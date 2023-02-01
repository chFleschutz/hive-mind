// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"

Cube::Cube()
{
}

Cube::~Cube()
{
}

Cube::Cube(int32 q, int32 r)
{
	Q = q;
	R = r;
	S = -q - r;
}

Cube::Cube(int32 q, int32 r, int32 s)
{
	Q = q;
	R = r;
	S = s;
}

Cube::Cube(const Cube& other)
{
	Q = other.Q;
	R = other.R;
	S = other.S;
}

Cube& Cube::operator=(const Cube& other)
{
	Q = other.Q;
	R = other.R;
	S = other.S;
	return *this;
}

Cube Cube::operator+(const Cube& other) const
{
	return Cube(Q + other.Q, R + other.R, S + other.S);
}

Cube& Cube::operator+=(const Cube& other)
{
	Q += other.Q;
	R += other.R;
	S += other.S;
	return *this;
}

Cube Cube::operator-(const Cube& other) const
{
	return Cube(Q - other.Q, R - other.R, S - other.S);
}

Cube& Cube::operator-=(const Cube& other)
{
	Q -= other.Q;
	R -= other.R;
	S -= other.S;
	return *this;
}

Cube Cube::Zero()
{
	return Cube(0, 0);
}

int32 Cube::distance(const Cube& a, const Cube& b)
{
	auto cube = a - b;
	return (abs(cube.Q) + abs(cube.R) + abs(cube.S)) / 2;
}

