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
	m_Q = q;
	m_R = r;
	m_S = -m_Q - m_R;	//< Make sure Q + R + S = 0
}

Cube::Cube(const Cube& other)
{
	m_Q = other.Q();
	m_R = other.R();
	m_S = other.S();
}

void Cube::SetQ(int32 newQ)
{
	m_Q = newQ;
	m_S = -m_Q - m_R;	//< Make sure Q + R + S = 0
}

void Cube::SetR(int32 newR)
{
	m_R = newR;
	m_S = -m_Q - m_R;	//< Make sure Q + R + S = 0
}

Cube& Cube::operator=(const Cube& other)
{
	m_Q = other.Q();
	m_R = other.R();
	m_S = other.S();
	return *this;
}

Cube Cube::operator+(const Cube& other) const
{
	return Cube(m_Q + other.Q(), m_R + other.R());
}

Cube& Cube::operator+=(const Cube& other)
{
	m_Q += other.Q();
	m_R += other.R();
	m_S += other.S();
	return *this;
}

Cube Cube::operator-(const Cube& other) const
{
	return Cube(m_Q - other.Q(), m_R - other.R());
}

Cube& Cube::operator-=(const Cube& other)
{
	m_Q -= other.Q();
	m_R -= other.R();
	m_S -= other.S();
	return *this;
}

bool Cube::operator==(const Cube& other) const
{
	return (m_Q == other.Q()) && (m_R == other.R()) && (m_S == other.S());
}

Cube Cube::Zero()
{
	return Cube(0, 0);
}

int32 Cube::distance(const Cube& a, const Cube& b)
{
	auto cube = a - b;
	return (abs(cube.Q()) + abs(cube.R()) + abs(cube.S())) / 2;
}

TArray<Cube> Cube::directionVectors()
{
	return TArray<Cube>() = { Cube(0, -1), Cube(1, -1), Cube(1, 0), Cube(0, 1), Cube(-1, 1), Cube(-1, 0) };
}

