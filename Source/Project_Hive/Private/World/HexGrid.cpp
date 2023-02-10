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

	auto gen = NewObject<UPerlinNoiseGenerator>();
	gen->Initialize(2 * GridSize + 1, NoiseCellSize, Seed);

	for (int32 q = -GridSize; q <= GridSize; q++)
	{
		for (int32 r = -GridSize; r <= GridSize; r++)
		{
			auto coord = FCube(q, r);
			if (FCube::Distance(coord, FCube::Zero()) > GridSize)
				continue;
			
			auto tileType = GetTileFor(coord, gen->PerlinNoise2D(q, r));
			SpawnTile(coord, tileType);
		}
	}

	CalculateNeighbors();
}

void AHexGrid::DestroyTiles()
{
	for (auto& entry : Grid)
	{
		entry.Value->Destroy();
	}
	Grid.Empty();
}

void AHexGrid::RandomizeSeed()
{
	Seed = FMath::Rand();
}

FVector AHexGrid::WorldLocation(const FCube& GridPosition)
{
	auto x = sqrt(3) * GridCellSize * (GridPosition.Q() + 0.5 * GridPosition.R());
	auto y = 3.0 / 2.0 * GridCellSize * GridPosition.R();
	return GridOrigin + FVector(x, y, 0.0);
}

void AHexGrid::SpawnTile(const FCube& GridPosition, TSubclassOf<ATile> TileToSpawn)
{
	auto world = GetWorld();
	if (!IsValid(world))
		return;

	if (!IsValid(TileToSpawn))
		return;

	auto location = WorldLocation(GridPosition);
	auto rotation = GetActorRotation();
	auto tile = world->SpawnActor<ATile>(TileToSpawn, location, rotation);

	if (!IsValid(tile))
		return;

	tile->SetGridPosition(GridPosition);
	tile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	Grid.Add(GridPosition, tile);
}

TSubclassOf<ATile> AHexGrid::GetTileFor(const FCube& GridPos, float Value)
{
	Value = Value + 1.0f;
	if (Value < SandValue)
		return SandTile;

	Value = Value - SandValue;
	if (Value < WaterValue)
		return WaterTile;

	return GrassTile;
}

void AHexGrid::CalculateNeighbors()
{
	for (auto& Element : Grid)
	{
		auto tile = Element.Value;
		auto position = Element.Key;
		for (const auto& direction : FCube::DirectionVectors())
		{
			auto neighborPosition = position + direction;
			if (auto neighbor = Grid.Find(neighborPosition))
				tile->AddNeighbor(*neighbor);
		}
	}
}
