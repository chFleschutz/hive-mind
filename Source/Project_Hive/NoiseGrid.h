// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_HIVE_API NoiseGrid
{
public:
	NoiseGrid(uint32 tileGridSize, uint32 noiseCellSize, uint32 seed = 0);
	~NoiseGrid();

	/** Returns the perlin noise value for the position (value between 0 and 1) */
	float perlinNoise2D(int32 posX, int32 posY);

private:
	// Returns a random unit FVector2D 
	FVector2D randomVec();

	float CornerGradientDotProduct(int32 cornerPosX, int32 cornerPosY, float posX, float posY);

	FVector2D noiseVec(uint32 x, uint32 y);

	TArray<FVector2D> Noise;
	int32 GridSize;
	int32 CellSize;
	uint32 Seed;
};
