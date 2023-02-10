// Fill out your copyright notice in the Description page of Project Settings.


#include "World/TerrainGeneration/PerlinNoiseGenerator.h"

#include "Math/UnrealMathUtility.h"


void UPerlinNoiseGenerator::Initialize(const int32 TileGridSize, const int32 NoiseCellSize, const uint32 InitSeed)
{
	Seed = InitSeed;
	CellSize = NoiseCellSize;
	GridSize = FMath::DivideAndRoundUp(TileGridSize, NoiseCellSize);
	FMath::RandInit(Seed);

	for (int32 x = -GridSize; x <= GridSize; x++)
	{
		for (int32 y = -GridSize; y <= GridSize; y++)
		{
			Noise.Emplace(RandomVec());
		}
	}
}

float UPerlinNoiseGenerator::PerlinNoise2D(const int32 PosX, const int32 PosY)
{
	// Coordinate conversion
	const float PositionX = static_cast<float>(PosX) / static_cast<float>(CellSize);
	const float PositionY = static_cast<float>(PosY) / static_cast<float>(CellSize);

	// Get corners of current cell 
	const int32 CornerX1 = FMath::Floor(PositionX);
	const int32 CornerX2 = CornerX1 + 1;
	const int32 CornerY1 = FMath::Floor(PositionY);
	const int32 CornerY2 = CornerY1 + 1;

	// Calculate dot product of random vec at corners and gradient vec (vec corner to position) and interpolate
	// For corners at X1
	const auto DotX1Y1 = CornerGradientDotProduct(CornerX1, CornerY1, PositionX, PositionY);
	const auto DotX1Y2 = CornerGradientDotProduct(CornerX1, CornerY2, PositionX, PositionY);
	const auto LerpX1 = FMath::Lerp(DotX1Y1, DotX1Y2, PositionY - FMath::Floor(PositionY));
	// For corners at X2
	const auto DotX2Y1 = CornerGradientDotProduct(CornerX2, CornerY1, PositionX, PositionY);
	const auto DotX2Y2 = CornerGradientDotProduct(CornerX2, CornerY2, PositionX, PositionY);
	const auto LerpX2 = FMath::Lerp(DotX2Y1, DotX2Y2, PositionY - FMath::Floor(PositionY));
	// Interpolate between dot products from X1 and X2
	return FMath::Lerp(LerpX1, LerpX2, PositionX - FMath::Floor(PositionX));
}

FVector2D UPerlinNoiseGenerator::RandomVec() const
{
	const auto RandAngle = FMath::FRand() * 2.0f * UE_PI;
	return FVector2D(FMath::Cos(RandAngle), FMath::Sin(RandAngle));
}

float UPerlinNoiseGenerator::CornerGradientDotProduct(const int32 CornerPosX, const int32 CornerPosY, const float PosX, const float PosY)
{
	const auto CornerVec = NoiseVec(CornerPosX, CornerPosY);
	auto GradientVec = FVector2D(PosX, PosY) - FVector2D(CornerPosX, CornerPosX);
	GradientVec.Normalize();
	return CornerVec.Dot(GradientVec);
}

FVector2D UPerlinNoiseGenerator::NoiseVec(const uint32 X, const uint32 Y)
{
	const auto ShiftedX = X + GridSize;
	const auto ShiftedY = Y + GridSize;
	const auto Index = ShiftedX * GridSize + ShiftedY;
	if (!Noise.IsValidIndex(Index))
		return FVector2D(1, 0);

	return Noise[Index];
}
