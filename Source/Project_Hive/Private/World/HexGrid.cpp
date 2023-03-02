// Fill out your copyright notice in the Description page of Project Settings.

#include "World/HexGrid.h"

#include "Utility/Cube.h"	
#include "Utility/DataStructs.h"
#include "Engine/DataTable.h"
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

	check(TilesDataTable);
	check(StructuresDataTable);

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

ATile* AHexGrid::SpawnTile(const FCube& GridPosition, const FTileData* TileData)
{
	const auto World = GetWorld();
	if (!IsValid(World))
		return nullptr;

	if (!TileData)
		return nullptr;

	const auto Location = WorldLocation(GridPosition);
	const auto Rotation = GetActorRotation();
	const auto Tile = World->SpawnActor<ATile>(TileData->TileClass, Location, Rotation);

	if (!IsValid(Tile))
		return nullptr;

	Tile->SetTileData(*TileData);
	Tile->SetGridPosition(GridPosition);
	Tile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Grid.Add(GridPosition, Tile);

	return Tile;
}

void AHexGrid::SpawnTileAt(const FCube& GridPos, float Value)
{
	// Evaluate RowName for value
	FName RowName;
	const auto SumValues = SandValue + WaterValue + GrassValue;
	if (Value < SandValue / SumValues)
	{
		RowName = "Sand";
	}
	else if (Value < (SandValue + WaterValue) / SumValues)
	{
		RowName = "Water";
		Value -= SandValue / SumValues;
	}
	else
	{
		RowName = "Grass";
		//Value -= (SandValue + WaterValue) / SumValues; // Take lower part of range
		Value = FMath::Abs(Value - ((SandValue + WaterValue + GrassValue) / SumValues)); // Take upper part of range
	}

	const auto TileData = TilesDataTable->FindRow<FTileData>(RowName, "Query for TileData");
	const auto Tile = SpawnTile(GridPos, TileData);

	if (!Tile) 
		return;

	// Build mountains and vegetation
	if (Value < TileData->MountainAmount)
	{
		const auto StructureData = StructuresDataTable->FindRow<FStructureData>(TileData->MountainStructure, "Query for MountainStructure");
		Tile->BuildStructure(StructureData);
	}
	else if (Value < TileData->VegetationAmount)
	{
		const auto StructureData = StructuresDataTable->FindRow<FStructureData>(TileData->VegetationStructure, "Query for VegetationStructure");
		Tile->BuildStructure(StructureData);
	}
}

void AHexGrid::SetAllNeighbors()
{
	for (const auto& Element : Grid)
	{
		const auto Tile = Element.Value;
		const auto Position = Element.Key;
		for (const auto& Direction : FCube::DirectionVectors())
		{
			auto NeighborPosition = Position + Direction;
			if (const auto Neighbor = Grid.Find(NeighborPosition))
				Tile->AddNeighbor(*Neighbor);
		}
	}
}
