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
		RandomSeed();

	auto gen = NewObject<UPerlinNoiseGenerator>();
	gen->initialize(2 * GridSize + 1, NoiseCellSize, Seed);

	for (int32 q = -GridSize; q <= GridSize; q++)
	{
		for (int32 r = -GridSize; r <= GridSize; r++)
		{
			auto coord = Cube(q, r);
			if (Cube::distance(coord, Cube::Zero()) > GridSize)
				continue;
			
			auto tile = GetTileFor(coord, gen->perlinNoise2D(q, r));
			SpawnTile(coord, tile);
		}
	}
}

void AHexGrid::DestroyTiles()
{
	for (const auto& tile : GeneratedTiles)
	{
		tile->Destroy();
	}
	GeneratedTiles.Empty();
}

void AHexGrid::RandomSeed()
{
	Seed = FMath::Rand();
}

FVector AHexGrid::WorldLocation(const Cube& gridPosition)
{
	auto x = sqrt(3) * GridCellSize * (gridPosition.Q + 0.5 * gridPosition.R);
	auto y = 3.0 / 2.0 * GridCellSize * gridPosition.R;
	return GridOrigin + FVector(x, y, 0.0);
}

void AHexGrid::SpawnTile(const Cube& gridPosition, TSubclassOf<ATile> tileToSpawn)
{
	auto world = GetWorld();
	if (!IsValid(world))
		return;

	if (!IsValid(tileToSpawn))
		return;

	auto location = WorldLocation(gridPosition);
	auto rotation = GetActorRotation();
	auto tile = world->SpawnActor<ATile>(tileToSpawn, location, rotation);

	if (!IsValid(tile))
		return;

	tile->setGridPosition(gridPosition);
	tile->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
	GeneratedTiles.Add(tile);
}

TSubclassOf<ATile> AHexGrid::GetTileFor(const Cube& gridPos, float value)
{
	value = value + 1.0f;
	if (value < SandValue)
		return SandTile;

	value = value - SandValue;
	if (value < WaterValue)
		return WaterTile;

	return GrassTile;
}
