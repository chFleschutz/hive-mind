// Fill out your copyright notice in the Description page of Project Settings.

#include "World/TerrainGeneration/RandomTerrainGenerator.h"

#include "Math/UnrealMathUtility.h"


URandomTerrainGenerator::URandomTerrainGenerator() 
{
}

void URandomTerrainGenerator::initialize(int32 tileGridSize, int32 noiseCellSize, uint32 seed)
{
	Seed = seed;
	CellSize = noiseCellSize;
	GridSize = FMath::DivideAndRoundUp(tileGridSize, noiseCellSize);
	FMath::RandInit(Seed);

	for (int32 x = -GridSize; x <= GridSize; x++)
	{
		for (int32 y = -GridSize; y <= GridSize; y++)
		{
			Noise.Emplace(randomVec());
		}
	}
}

float URandomTerrainGenerator::perlinNoise2D(int32 posX, int32 posY)
{
	// Coordinate conversion
	const float positionX = (float)posX / (float)CellSize;
	const float positionY = (float)posY / (float)CellSize;

	// Get corners of current cell 
	int32 cornerX1 = FMath::Floor(positionX);
	int32 cornerX2 = cornerX1 + 1;
	int32 cornerY1 = FMath::Floor(positionY);
	int32 cornerY2 = cornerY1 + 1;

	// Calculate dot product of random vec at corners and gradient vec (vec corner to position) and interpolate
	// For corners at X1
	auto dotX1Y1 = CornerGradientDotProduct(cornerX1, cornerY1, positionX, positionY);
	auto dotX1Y2 = CornerGradientDotProduct(cornerX1, cornerY2, positionX, positionY);
	auto lerpX1 = FMath::Lerp(dotX1Y1, dotX1Y2, positionY - FMath::Floor(positionY));
	// For corners at X2
	auto dotX2Y1 = CornerGradientDotProduct(cornerX2, cornerY1, positionX, positionY);
	auto dotX2Y2 = CornerGradientDotProduct(cornerX2, cornerY2, positionX, positionY);
	auto lerpX2 = FMath::Lerp(dotX2Y1, dotX2Y2, positionY - FMath::Floor(positionY));
	// Interpolate between dot products from X1 and X2
	return FMath::Lerp(lerpX1, lerpX2, positionX - FMath::Floor(positionX));
}

FVector2D URandomTerrainGenerator::randomVec()
{
	auto randAngle = FMath::FRand() * 2.0f * UE_PI;
	return FVector2D(FMath::Cos(randAngle), FMath::Sin(randAngle));
}

float URandomTerrainGenerator::CornerGradientDotProduct(int32 cornerPosX, int32 cornerPosY, float posX, float posY)
{
	auto cornerVec = noiseVec(cornerPosX, cornerPosY);
	auto gradientVec = FVector2D(posX, posY) - FVector2D(cornerPosX, cornerPosX);
	gradientVec.Normalize();
	return cornerVec.Dot(gradientVec);
}

FVector2D URandomTerrainGenerator::noiseVec(uint32 x, uint32 y)
{
	auto shiftedX = x + GridSize;
	auto shiftedY = y + GridSize;
	auto index = shiftedX * GridSize + shiftedY;
	if (!Noise.IsValidIndex(index))
		return FVector2D(1, 0);

	return Noise[index];
}
