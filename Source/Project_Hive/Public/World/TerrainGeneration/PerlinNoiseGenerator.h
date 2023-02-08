// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "World/TerrainGeneration/RandomTerrainGenerator.h"
#include "PerlinNoiseGenerator.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API UPerlinNoiseGenerator : public URandomTerrainGenerator
{
	GENERATED_BODY()
	
public:
	void initialize(int32 tileGridSize, int32 noiseCellSize, uint32 seed = 0);

	/** Returns the perlin noise value for the position (value between -1 and 1) */
	float perlinNoise2D(int32 posX, int32 posY);

protected:
	// Returns a random unit FVector2D 
	FVector2D randomVec();

	float CornerGradientDotProduct(int32 cornerPosX, int32 cornerPosY, float posX, float posY);

	FVector2D noiseVec(uint32 x, uint32 y);

	TArray<FVector2D> Noise;
	int32 GridSize;
	int32 CellSize;
	uint32 Seed;
};
