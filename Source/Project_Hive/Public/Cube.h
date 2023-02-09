// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class PROJECT_HIVE_API Cube
{
public:
	Cube();
	~Cube();
	Cube(int32 q, int32 r);
	Cube(const Cube& other);

	inline int32 Q() const { return m_Q; }
	inline int32 R() const { return m_R; }
	inline int32 S() const { return m_S; }

	void SetQ(int32 newQ);
	void SetR(int32 newR);

	Cube& operator=(const Cube& other);

	Cube operator+(const Cube& other) const;
	Cube& operator+=(const Cube& other);

	Cube operator-(const Cube& other) const;
	Cube& operator-=(const Cube& other);

	bool operator==(const Cube& other) const;

	static Cube Zero();

	static int32 distance(const Cube& a, const Cube& b);

	static TArray<Cube> directionVectors();

private:
	// Coordinates q, r, s (constraint q + r + s = 0)
	int32 m_Q = 0;
	int32 m_R = 0;
	int32 m_S = 0;	//< Precomputed s coordinate read only 
};

FORCEINLINE uint32 GetTypeHash(const Cube& cube)
{
	uint32 Hash = FCrc::MemCrc32(&cube, sizeof(Cube));
	return Hash;
}
