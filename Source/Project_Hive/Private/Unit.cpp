// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#include "AI/Unit.h"

#include "World/Tiles/Tile.h"
#include "AI/AStarNavigation.h"
#include "AI/UnitAIController.h"
#include "TurnBasedGameMode.h"
#include "Components/CapsuleComponent.h"
#include "Engine/StaticMeshSocket.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUnit::AUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(RootComponent);
}

// Called every frame
void AUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AUnit::OnPlanningPhaseStarted()
{
}

void AUnit::OnExecutionPhaseStarted()
{
	if (MovementPath.IsEmpty())
		return;
	
	if (const auto GameMode = Cast<ATurnBasedGameMode>(UGameplayStatics::GetGameMode(this)))
	{
		GameMode->ObjectExecutionStarted();
	}

	StartMoveToTarget();
}

void AUnit::SetStandingTile(ATile* Tile)
{
	if (!Tile->CanPlaceUnit())
		return;

	StandingTile = Tile;
	StandingTile->PlaceUnit(this);
	SetActorLocation(StandingTile->GetActorLocation() + FVector(0.0, 0.0, 100.0));
}

bool AUnit::CanMoveTo(ATile* Tile)
{
	if (!Tile)
		return false;

	return !Tile->BlocksMovement() && UnitMovementTypes.Contains(Tile->GetType());
}

void AUnit::SetMoveTarget(ATile* TargetTile)
{
	if (FCube::Distance(StandingTile->GetGridPosition(), TargetTile->GetGridPosition()) > MovementRange)
		return;

	// Get path with AStar
	MovementPath.Empty();
	MovementPath = UAStarNavigation::GetPath(StandingTile, TargetTile, this);

	// Draw path with lines
	auto LastTile = StandingTile;
	for (const auto Tile : MovementPath)
	{
		const auto Start = LastTile->GetActorLocation() + FVector(0.0, 0.0, 110.0);
		const auto End = Tile->GetActorLocation() + FVector(0.0, 0.0, 110.0);
		DrawDebugLine(GetWorld(), Start, End, FColor::Cyan, false, 10.0f, 0, 5.0f);

		LastTile = Tile;
	}
}

void AUnit::StartMoveToTarget()
{
	MoveToNextTileOnPath();
}

void AUnit::MoveToNextTileOnPath()
{
	if (MovementPath.IsEmpty())
		return;

	const auto NextTile = MovementPath[0];
	MovementPath.RemoveAt(0);
	MoveToTile(NextTile);
}

void AUnit::OnMoveToTileFinished()
{
	IsMoving = false;
	if (!MovementPath.IsEmpty())
	{
		MoveToNextTileOnPath();
		return;
	}
	// Signal finished
	if (const auto World = GetWorld())
	{
		if (const auto GameMode = Cast<ATurnBasedGameMode>(UGameplayStatics::GetGameMode(World)))
		{
			GameMode->ObjectExecutionFinished();
		}
	}
}

// Called when the game starts or when spawned
void AUnit::BeginPlay()
{
	Super::BeginPlay();

	const auto Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = 300.0f;

	MeshComponent->SetCollisionProfileName(TEXT("UnitPreset"));

	const auto World = GetWorld();
	if (!World)
		return;
	// Connect to game-mode events
	if (const auto GameMode = Cast<ATurnBasedGameMode>(UGameplayStatics::GetGameMode(World)))
	{
		//GameMode->OnPlanningPhaseStartedEvent().AddUObject(this, &AUnit::OnPlanningPhaseStarted);
		//GameMode->OnExecutionPhaseStartedEvent().AddUObject(this, &AUnit::OnExecutionPhaseStarted);
		GameMode->OnPlanningPhaseStarted.AddDynamic(this, &AUnit::OnPlanningPhaseStarted);
		GameMode->OnExecutionPhaseStarted.AddDynamic(this, &AUnit::OnExecutionPhaseStarted);
	}
}

void AUnit::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void AUnit::MoveToTile(ATile* NextTile)
{
	if (!NextTile->CanPlaceUnit())
		return;

	const auto AIController = GetController<AUnitAIController>();
	if (!AIController)
		return;

	IsMoving = true;
	// Update pointers on tiles
	StandingTile->RemoveUnit();
	NextTile->PlaceUnit(this);
	StandingTile = NextTile;
	// Start to move in scene
	const auto Location = NextTile->GetCenterSocketLocation();
	AIController->MoveToLocation(Location, -1, false, false);
}
