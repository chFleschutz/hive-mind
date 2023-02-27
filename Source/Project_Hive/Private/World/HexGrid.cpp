// Fill out your copyright notice in the Description page of Project Settings.

#include "World/HexGrid.h"

#include "Cube.h"
#include "World/TerrainGeneration/PerlinNoiseGenerator.h"
#include "World/Tiles/Tile.h"


// Sets default values
AHexGrid::AHexGrid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHexGrid::BeginPlay()
{
	Super::BeginPlay();
	Generate();
}

// Called every frame
void AHexGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexGrid::Generate()
{
	DestroyTiles();
	GenerateCircle();
}

void AHexGrid::GenerateCircle()
{
	if (AutoGenerateRandomSeed)
		RandomizeSeed();

	const auto Gen = NewObject<UPerlinNoiseGenerator>();
	Gen->Initialize(2 * GridSize + 1, NoiseCellSize, Seed);

	for (int32 q = -GridSize; q <= GridSize; q++)
	{
		for (int32 r = -GridSize; r <= GridSize; r++)
		{
			auto Cord = FCube(q, r);
			if (FCube::Distance(Cord, FCube::Zero()) > GridSize)
				continue;

			const auto Value = (Gen->PerlinNoise2D(q, r) + 1.0f) / 2.0f; // Map to 0 - 1 Range
			SpawnTileAt(Cord, Value);
		}
	}

	SetAllNeighbors();
}

void AHexGrid::DestroyTiles()
{
	for (const auto& Entry : Grid)
	{
		Entry.Value->Destroy();
	}
	Grid.Empty();
}

void AHexGrid::RandomizeSeed()
{
	Seed = FMath::Rand();
}

FVector AHexGrid::WorldLocation(const FCube& GridPosition) const
{
	const auto x = sqrt(3) * GridCellSize * (GridPosition.Q() + 0.5 * GridPosition.R());
	const auto y = 3.0 / 2.0 * GridCellSize * GridPosition.R();
	return GridOrigin + FVector(x, y, 0.0);
}

ATile* AHexGrid::SpawnTile(const FCube& GridPosition, const TSubclassOf<ATile> TileToSpawn)
{
	const auto World = GetWorld();
	if (!IsValid(World))
		return nullptr;

	if (!IsValid(TileToSpawn))
		return nullptr;

	const auto Location = WorldLocation(GridPosition);
	const auto Rotation = GetActorRotation();
	const auto Tile = World->SpawnActor<ATile>(TileToSpawn, Location, Rotation);

	if (!IsValid(Tile))
		return nullptr;

	Tile->SetGridPosition(GridPosition);
	Tile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Grid.Add(GridPosition, Tile);

	return Tile;
}

TSubclassOf<ATile> AHexGrid::GetTileFor(const FCube& GridPos, float Value) const
{
	const auto SumValues = SandValue + WaterValue + GrassValue;
	if (Value < (SandValue / SumValues))
	{
		return SandTile;
	}
	else if (Value < (SandValue + WaterValue) / SumValues)
	{
		return WaterTile;
	}
	else
	{
		return GrassTile;
	}
}

void AHexGrid::SpawnTileAt(const FCube& GridPos, const float Value)
{
	const auto SumValues = SandValue + WaterValue + GrassValue;
	if (Value < SandValue / SumValues)
	{	// Sand Tile
		const auto Tile = SpawnTile(GridPos, SandTile);
		if (Value < MountainAmount)
		{
			Tile->BuildMountain();
		}
		else if (Value < DesertVegetationAmount)
		{
			Tile->BuildVegetation();
		}
	}
	else if (Value < (SandValue + WaterValue) / SumValues)
	{	// Water Tile
		SpawnTile(GridPos, WaterTile);
	}
	else
	{	// Grass Tile
		const auto Tile = SpawnTile(GridPos, GrassTile);
		if (Value > 1.0f - MountainAmount)
		{
			Tile->BuildMountain();
		}
		else if (Value > 1.0f - ForestAmount)
		{
			Tile->BuildVegetation();
		}
	}
}

void AHexGrid::SetAllNeighbors()
{
	for (const auto& Element : Grid)
	{
		const auto Tile = Element.Value;
		auto Position = Element.Key;
		for (const auto& Direction : FCube::DirectionVectors())
		{
			auto NeighborPosition = Position + Direction;
			if (const auto Neighbor = Grid.Find(NeighborPosition))
				Tile->AddNeighbor(*Neighbor);
		}
	}
}
