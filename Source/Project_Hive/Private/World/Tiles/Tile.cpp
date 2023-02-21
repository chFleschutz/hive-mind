// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#include "World/Tiles/Tile.h"

#include "AI/NavigableUnit.h"
#include "World/Structures/TileStructure.h"
#include "World/Structures/TileVegetation.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));

	HexTileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	HexTileMesh->SetupAttachment(RootComponent);

	CenterSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Center Socket"));
	CenterSocket->SetupAttachment((HexTileMesh));
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	HexTileMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::SetSelected(const bool IsSelected, const bool ShowRangeOfUnit)
{
	IsTileSelected = IsSelected;

	if (HexTileMesh)
		HexTileMesh->SetRenderCustomDepth(IsSelected);

	if (ShowRangeOfUnit && PlacedUnit)
		DisplayMovementRange(IsSelected);
}

void ATile::SetNeighborsSelected(const bool IsSelected, const int32 Depth) 
{
	if (Depth <= 0)
		return;

	for (const auto Neighbor : Neighbors)
	{
		if (Neighbor->GetIsSelected() == IsSelected)
			continue;

		Neighbor->SetSelected(IsSelected);
		Neighbor->SetNeighborsSelected(IsSelected, Depth - 1);
	}
}

bool ATile::CanDestroyBuilding() const
{
	return static_cast<bool>(Structure);
}

bool ATile::CanBuild(ATileStructure* NewStructure)
{
	if (!IsValid(NewStructure))
		return false;
	if (Structure) // If tile already has a structure
		return false;

	return NewStructure->CheckFoundationSupport(TileFoundationType);
}

void ATile::Build(ATileStructure* NewStructure)
{
	if (!CanBuild(NewStructure))
		return;

	AppendStructure(NewStructure);
}

void ATile::DestroyBuilding()
{
	if (Structure)
	{
		Structure->Destroy();
		Structure = nullptr;
	}
}

bool ATile::CanPlaceUnit()
{
	return !PlacedUnit;
}

bool ATile::PlaceUnit(ANavigableUnit* Unit)
{
	if (!CanPlaceUnit())
		return false;

	PlacedUnit = Unit;
	QueryTilesInMovementRange();
	if (IsTileSelected)
		DisplayMovementRange(true);

	return true;
}

void ATile::RemoveUnit()
{
	PlacedUnit = nullptr; 
	DisplayMovementRange(false);
	TilesInMovementRange.Empty();
}

void ATile::BuildVegetation()
{
	BuildStructure(VegetationType);
}

void ATile::BuildMountain()
{
	BuildStructure(MountainType);
}

void ATile::SetGridPosition(const FCube& Position)
{
	GridPosition = Position;
}

void ATile::AddNeighbor(ATile* Neighbor)
{
	Neighbors.Emplace(Neighbor);
}

void ATile::AppendStructure(ATileStructure* NewStructure)
{
	Structure = NewStructure;
	Structure->SetActorLocation(CenterSocket->GetComponentLocation());
	const FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, false);
	Structure->AttachToActor(this, Rules);
}

void ATile::BuildStructure(const TSubclassOf<ATileStructure> StructureType)
{
	if (!IsValid(StructureType))
		return;

	if (Structure)
		return;

	if (const auto World = GetWorld())
	{
		const auto Location = CenterSocket->GetComponentLocation();
		const auto Rotation = FRotator(0.0, 60.0 * FMath::RandRange(0, 5), 0.0);
		const auto NewStructure = World->SpawnActor<ATileStructure>(StructureType, Location, Rotation);
		AppendStructure(NewStructure);
	}
}

void ATile::QueryTilesInMovementRange()
{
	if (!PlacedUnit)
		return;

	TArray<ATile*> Frontier;
	Frontier.Add(this);
	TilesInMovementRange.Add(this);

	const auto MovementRange = PlacedUnit->GetMovementRange();
	int32 CurrentLevel = 0;
	int32 RemainingTilesInLevel = 1;

	while (!Frontier.IsEmpty())
	{
		const auto CurrentTile = Frontier[0];
		Frontier.RemoveAt(0);
		RemainingTilesInLevel--;

		for (const auto NextTile : CurrentTile->GetNeighbors())
		{
			if (!PlacedUnit->CanMoveTo(NextTile)) //< Skip impossible tiles
				continue;
			if (TilesInMovementRange.Contains(NextTile))	//< Skip already visited tiles
				continue;

			Frontier.Add(NextTile);
			TilesInMovementRange.Add(NextTile);
		}

		if (RemainingTilesInLevel == 0)
		{
			RemainingTilesInLevel = Frontier.Num();
			CurrentLevel++;
			if (CurrentLevel == MovementRange)
				break;
		}
	}
}

void ATile::DisplayMovementRange(const bool IsVisible)
{
	for (const auto Tile: TilesInMovementRange)
	{
		Tile->SetSelected(IsVisible, false);
	}

	if (IsTileSelected)
		SetSelected(true, false);
}
