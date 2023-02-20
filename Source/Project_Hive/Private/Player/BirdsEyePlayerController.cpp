// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "Player/BirdsEyePlayerController.h"

#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AI/NavigableUnit.h"
#include "Player/BirdsEyePlayer.h"
#include "Player/BuildComponent.h"

#include "World/Tiles/Tile.h"
#include "World/Structures/TileStructure.h"


ABirdsEyePlayerController::ABirdsEyePlayerController()
{
	BuildComponent = static_cast<UBuildComponent*>(AddComponentByClass(BuildComponentClass, false, FTransform(), false));
}
// Called when the game starts or when spawned
void ABirdsEyePlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Set Input Mapping
	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMapping, 0);
		Subsystem->AddMappingContext(SelectMapping, 1);
	}

	SetControlRotation(FRotator(300.0, 0.0, 0.0));
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

// Called every frame
void ABirdsEyePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PreviewStructure)
	{
		const auto HoveredTile = QueryTileUnderCursor();
		if (!HoveredTile)
			return;

		const auto Location = HoveredTile->GetActorLocation() + FVector(0.0, 0.0, 100.0);
		PreviewStructure->SetActorLocation(Location);
	}
}

// Called to bind functionality to input
void ABirdsEyePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (const auto Input = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		Input->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayerController::Zoom);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayerController::Look);
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayerController::Move);
		Input->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayerController::Select);
		Input->BindAction(MoveTargetAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayerController::MoveToTarget);
	}
}

bool ABirdsEyePlayerController::HasTileSelected() const
{
	return static_cast<bool>(SelectedTile);
}

void ABirdsEyePlayerController::ToggleBuildMode(const bool IsActive) const
{
	if (const auto Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (IsActive)
		{
			Subsystem->RemoveMappingContext(SelectMapping);
			Subsystem->AddMappingContext(BuildModeMapping, 1);
		}
		else
		{
			Subsystem->RemoveMappingContext(BuildModeMapping);
			Subsystem->AddMappingContext(SelectMapping, 1);
		}
	}
}

bool ABirdsEyePlayerController::CanSpawnCharacter() const
{
	if (!SelectedTile)
		return false;

	return SelectedTile->CanPlaceUnit();
}

void ABirdsEyePlayerController::SpawnUnit(const TSubclassOf<ANavigableUnit> Unit) const
{
	if (!SelectedTile->CanPlaceUnit())
		return;

	if (const auto World = GetWorld())
	{
		const auto Location = SelectedTile->GetActorLocation() + FVector(0.0, 0.0, 100.0);
		const auto Rotation = FRotator::ZeroRotator;
		const auto NewCharacter = World->SpawnActor<ANavigableUnit>(Unit, Location, Rotation);
		NewCharacter->SetStandingTile(SelectedTile);
	}
}

ATile* ABirdsEyePlayerController::QueryTileUnderCursor() const
{
	FHitResult Hit;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	GetHitResultUnderCursorForObjects(ObjectTypesArray, false, Hit);

	if (!Hit.IsValidBlockingHit())
		return nullptr;

	const auto HitActor = Hit.GetActor();
	if (!IsValid(HitActor))
		return nullptr;

	return Cast<ATile>(HitActor);
}

// ReSharper disable once CppMemberFunctionMayBeConst because input-action-callback cannot be const
void ABirdsEyePlayerController::Zoom(const FInputActionValue& Value)
{
	if (const auto ControlledPawn = GetPawn<ABirdsEyePlayer>())
	{
		ControlledPawn->AddZoomInput(Value.Get<float>());
	}
}

void ABirdsEyePlayerController::Look(const FInputActionValue& Value)
{
	const auto LookInput = Value.Get<FVector2D>();
	AddYawInput(LookInput.X);
	AddPitchInput(LookInput.Y);
}

// ReSharper disable once CppMemberFunctionMayBeConst because input-action-callback cannot be const
void ABirdsEyePlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (const auto ControlledPawn = GetPawn())
	{
		// Calculate forward and right direction
		const auto Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		ControlledPawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABirdsEyePlayerController::Select(const FInputActionValue& Value)
{
	// Deselect last selection
	if (SelectedTile)
	{
		SelectedTile->SetSelected(false);
		SelectedTile = nullptr;
	}
	// Select new tile
	if (const auto Tile = QueryTileUnderCursor())
	{
		Tile->SetSelected(true);
		SelectedTile = Tile;
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst (Input Action)
void ABirdsEyePlayerController::MoveToTarget(const FInputActionValue& Value)
{
	if (!SelectedTile)
		return;

	const auto TargetTile = QueryTileUnderCursor();
	const auto SelectedCharacter = SelectedTile->GetUnit();
	if (TargetTile && SelectedCharacter)
	{
		SelectedCharacter->SetMoveTarget(TargetTile);
	}
}
