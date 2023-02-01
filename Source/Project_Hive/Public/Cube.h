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
	Cube(int32 q, int32 r, int32 s);
	Cube(const Cube& other);

	Cube& operator=(const Cube& other);

	Cube operator+(const Cube& other) const;
	Cube& operator+=(const Cube& other);

	Cube operator-(const Cube& other) const;
	Cube& operator-=(const Cube& other);

	static Cube Zero();

	static int32 distance(const Cube& a, const Cube& b);

	int32 Q = 0;
	int32 R = 0;
	int32 S = 0;
};
