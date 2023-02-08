// Fill out your copyright notice in the Description page of Project Settings.

#include "Player/BirdsEyePlayer.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Engine/CollisionProfile.h"

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
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}

		PlayerController->PlayerCameraManager->ViewPitchMin = MinPitchAngle;
		PlayerController->PlayerCameraManager->ViewPitchMax = MaxPitchAngle;
	}

	// Setup controller
	Controller;
	auto controller = UGameplayStatics::GetPlayerController(this->GetWorld(), 0);
	if (controller)
	{
		controller->SetControlRotation(FRotator(330.0, 60.0, 0.0));
		controller->bShowMouseCursor = true;
		controller->DefaultMouseCursor = EMouseCursor::Default;
	}
}

// Called every frame
void ABirdsEyePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (PreviewStructure)
	{
		auto HoveredTile = QueryTileUnderCursor();
		if (!HoveredTile)
			return;

		auto location = HoveredTile->GetActorLocation() + FVector(0.0, 0.0, 100.0);
		PreviewStructure->SetActorLocation(location);
	}
}

// Called to bind functionality to input
void ABirdsEyePlayer::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (auto Input = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		Input->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Zoom);
		Input->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Look);
		Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Move);
		Input->BindAction(SelectAction, ETriggerEvent::Triggered, this, &ABirdsEyePlayer::Select);
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

void ABirdsEyePlayer::startBuildingStructure(TSubclassOf<ATileStructure> structure)
{
	// show preview
	if (auto tile = QueryTileUnderCursor())
	{
		if (!IsValid(structure))
			return;

		auto world = GetWorld();
		if (!IsValid(world))
			return;

		auto Location = tile->GetActorLocation() + FVector(0.0, 0.0, 100.0);
		auto Rotation = FRotator(0.0, 60.0 * FMath::RandRange(0, 5), 0.0);
		PreviewStructure = world->SpawnActor<ATileStructure>(structure, Location, Rotation);
	}
}

void ABirdsEyePlayer::Zoom(const FInputActionValue& Value)
{
	auto ArmLength = SpringArm->TargetArmLength + (Value.Get<float>() * ZoomSpeed);
	SpringArm->TargetArmLength = FMath::Clamp(ArmLength, MinCameraZoom, MaxCameraZoom);
}

void ABirdsEyePlayer::Look(const FInputActionValue& Value)
{
	auto lookInput = Value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(lookInput.X);
		AddControllerPitchInput(lookInput.Y);
	}
}

void ABirdsEyePlayer::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();
	if (Controller)
	{
		// Calculate forward and right direction
		auto Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		auto ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		auto RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABirdsEyePlayer::Select(const FInputActionValue& Value)
{
	// Finally build preview tile
	if (PreviewStructure)
	{
		if (auto tile = QueryTileUnderCursor())
		{
			tile->Build(PreviewStructure);
			PreviewStructure = nullptr;
			return;
		}
	}

	// Deselect last selection
	if (SelectedTile)
	{
		SelectedTile->SetSelected(false);
		SelectedTile = nullptr;
	}

	if (auto tile = QueryTileUnderCursor())
	{
		tile->SetSelected(true);
		SelectedTile = tile;
	}
}

ATile* ABirdsEyePlayer::QueryTileUnderCursor()
{
	auto playerController = GetWorld()->GetFirstPlayerController();
	if (!playerController)
		return nullptr;

	FHitResult Hit;
	TArray<TEnumAsByte<EObjectTypeQuery>> objectTypesArray;
	objectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	playerController->GetHitResultUnderCursorForObjects(objectTypesArray, false, Hit);

	if (!Hit.IsValidBlockingHit())
		return nullptr;

	auto HitActor = Hit.GetActor();
	if (!IsValid(HitActor))
		return nullptr;

	return Cast<ATile>(HitActor);
}
