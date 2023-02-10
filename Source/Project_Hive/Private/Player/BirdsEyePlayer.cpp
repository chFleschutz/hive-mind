// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BirdsEyePlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AI/NavigationCharacter.h"

#include "World/Tiles/Tile.h"
#include "World/Structures/TileStructure.h"


// Sets default values
ABirdsEyePlayer::ABirdsEyePlayer()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Setup Scene Root
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));

	// visible mesh
	InvisibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	InvisibleMesh->SetupAttachment(RootComponent);

	// Setup Camera
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(InvisibleMesh);
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bEnableCameraLag = false;
	SpringArm->TargetArmLength = 1500.0f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingMovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ABirdsEyePlayer::BeginPlay()
{
	Super::BeginPlay();

	// Set Input Mapping
	if (const auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}

		PlayerController->PlayerCameraManager->ViewPitchMin = MinPitchAngle;
		PlayerController->PlayerCameraManager->ViewPitchMax = MaxPitchAngle;

		PlayerController->SetControlRotation(FRotator(330.0, 60.0, 0.0));
		PlayerController->bShowMouseCursor = true;
		PlayerController->DefaultMouseCursor = EMouseCursor::Default;
	}
}

// Called every frame
void ABirdsEyePlayer::Tick(float DeltaTime)
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
void ABirdsEyePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (const auto Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Zoom);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Look);
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Move);
		Input->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Select);
		Input->BindAction(MoveTargetAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::MoveToTarget);
	}
}

void ABirdsEyePlayer::BuildOnSelectedTile()
{
	//if (SelectedTile)
	//	SelectedTile->Build(DefaultStructure);
}

void ABirdsEyePlayer::DestroyBuildingOnSelectedTile()
{
	if (SelectedTile)
		SelectedTile->DestroyBuilding();
}

bool ABirdsEyePlayer::CanBuild()
{
	if (!SelectedTile)
		return false;

	return SelectedTile->CanBuild();
}

bool ABirdsEyePlayer::CanDestroyBuilding()
{
	if (!SelectedTile)
		return false;

	return SelectedTile->CanDestroyBuilding();
}

bool ABirdsEyePlayer::HasTileSelected()
{
	return static_cast<bool>(SelectedTile);
}

void ABirdsEyePlayer::StartBuildingStructure(const TSubclassOf<ATileStructure> Structure)
{
	// show preview
	if (!IsValid(Structure))
		return;

	const auto World = GetWorld();
	if (!IsValid(World))
		return;

	const auto Location = FVector::Zero();
	const auto Rotation = FRotator(0.0, 60.0 * FMath::RandRange(0, 5), 0.0);
	PreviewStructure = World->SpawnActor<ATileStructure>(Structure, Location, Rotation);
}

bool ABirdsEyePlayer::CanSpawnCharacter() const
{
	if (!SelectedTile)
		return false;

	return SelectedTile->CanTakeCharacter();
}

void ABirdsEyePlayer::SpawnCharacter(const TSubclassOf<ANavigationCharacter> Character) const
{
	if (!SelectedTile || !SelectedTile->CanTakeCharacter())
		return;

	if (const auto World = GetWorld())
	{
		const auto Location = SelectedTile->GetActorLocation() + FVector(0.0, 0.0, 100.0);
		const auto Rotation = FRotator::ZeroRotator;
		const auto NewCharacter = World->SpawnActor<ANavigationCharacter>(Character, Location, Rotation);
		NewCharacter->SetStandingTile(SelectedTile);
	}
}

// ReSharper disable once CppMemberFunctionMayBeConst because used as Input Action cant be made const
void ABirdsEyePlayer::Zoom(const FInputActionValue& Value) 
{
	const auto ArmLength = SpringArm->TargetArmLength + (Value.Get<float>() * ZoomSpeed);
	SpringArm->TargetArmLength = FMath::Clamp(ArmLength, MinCameraZoom, MaxCameraZoom);
}

void ABirdsEyePlayer::Look(const FInputActionValue& Value)
{
	const auto LookInput = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookInput.X);
		AddControllerPitchInput(LookInput.Y);
	}
}

void ABirdsEyePlayer::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller)
	{
		// Calculate forward and right direction
		const auto Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABirdsEyePlayer::Select(const FInputActionValue& Value)
{
	// Finally build preview tile
	if (PreviewStructure)
	{
		const auto Tile = QueryTileUnderCursor();
		if (!Tile)
			return;

		if (!Tile->CanBuild(PreviewStructure))
			return;

		Tile->Build(PreviewStructure);
		PreviewStructure = nullptr;
		return;
	}

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
void ABirdsEyePlayer::MoveToTarget(const FInputActionValue& Value)
{
	if (!SelectedTile)
		return;

	const auto TargetTile = QueryTileUnderCursor();
	const auto SelectedCharacter = SelectedTile->GetCharacter();
	if (TargetTile && SelectedCharacter)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Tile Selected"));

		SelectedCharacter->SetMoveTarget(TargetTile);
	}
}

ATile* ABirdsEyePlayer::QueryTileUnderCursor() const
{
	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
		return nullptr;

	FHitResult Hit;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	PlayerController->GetHitResultUnderCursorForObjects(ObjectTypesArray, false, Hit);

	if (!Hit.IsValidBlockingHit())
		return nullptr;

	const auto HitActor = Hit.GetActor();
	if (!IsValid(HitActor))
		return nullptr;

	return Cast<ATile>(HitActor);
}
