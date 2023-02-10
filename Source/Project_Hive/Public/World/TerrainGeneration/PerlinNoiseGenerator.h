// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/TerrainGeneration/RandomTerrainGenerator.h"
#include "PerlinNoiseGenerator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API UPerlinNoiseGenerator final : public URandomTerrainGenerator
{
	GENERATED_BODY()
	
public:
	void Initialize(int32 TileGridSize, int32 NoiseCellSize, uint32 InitSeed = 0);

	/** Returns the perlin noise value for the position (value between -1 and 1) */
	float PerlinNoise2D(int32 PosX, int32 PosY);

protected:
	// Returns a random unit FVector2D 
	FVector2D RandomVec() const;

	float CornerGradientDotProduct(int32 CornerPosX, int32 CornerPosY, float PosX, float PosY);

	FVector2D NoiseVec(uint32 X, uint32 Y);

	TArray<FVector2D> Noise;
	int32 GridSize;
	int32 CellSize;
	uint32 Seed;
};
