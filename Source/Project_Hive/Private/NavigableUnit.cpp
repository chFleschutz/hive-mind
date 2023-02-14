// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#include "AI/NavigableUnit.h"

#include "World/Tiles/Tile.h"
#include "AI/AStarNavigation.h"
#include "AI/UnitAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
ANavigableUnit::ANavigableUnit()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

}

// Called when the game starts or when spawned
void ANavigableUnit::BeginPlay()
{
	Super::BeginPlay();

	auto Movement = GetCharacterMovement();
	Movement->MaxWalkSpeed = 300.0f;
}

void ANavigableUnit::MoveToNextTileOnPath()
{
	if (MovementPath.IsEmpty())
		return;

	const auto NextTile = MovementPath[0];
	MovementPath.RemoveAt(0);
	MoveToTile(NextTile);
}

void ANavigableUnit::OnMoveToTileFinished()
{
	IsMoving = false;
	MoveToNextTileOnPath();
}

// Called every frame
void ANavigableUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANavigableUnit::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANavigableUnit::SetStandingTile(ATile* Tile)
{
	if (!Tile->CanPlaceUnit())
		return;

	StandingTile = Tile;
	StandingTile->PlaceUnit(this);
	SetActorLocation(StandingTile->GetActorLocation() + FVector(0.0, 0.0, 100.0));
}

bool ANavigableUnit::CanMoveTo(ATile* Tile)
{
	return UnitType == Tile->GetType();
}

void ANavigableUnit::SetMoveTarget(ATile* TargetTile)
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

	// Start Moving
	MoveToNextTileOnPath();
}

void ANavigableUnit::MoveToTile(ATile* NextTile)
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
