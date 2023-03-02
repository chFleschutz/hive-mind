// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_HIVE_API FCube 
{
public:
	FCube();
	FCube(int32 Q, int32 R);
	FCube(const FCube& Other);
	FCube(const FCube&& Other);

	inline int32 Q() const { return M_Q; }
	inline int32 R() const { return M_R; }
	inline int32 S() const { return M_S; }

	void SetQ(int32 NewQ);
	void SetR(int32 NewR);

	FCube& operator=(const FCube& Other);

	FCube operator+(const FCube& Other) const;
	FCube& operator+=(const FCube& Other);

	FCube operator-(const FCube& Other) const;
	FCube& operator-=(const FCube& Other);

	bool operator==(const FCube& Other) const;

	static FCube Zero();

	static float Distance(const FCube& A, const FCube& B);

	static TArray<FCube> DirectionVectors();

private:
	// Coordinates q, r, s (constraint q + r + s = 0)
	int32 M_Q = 0;
	int32 M_R = 0;
	int32 M_S = 0;	//< Precomputed s coordinate read only 
};

FORCEINLINE uint32 GetTypeHash(const FCube& Cube)
{
	return FCrc::MemCrc32(&Cube, sizeof(FCube));
}
