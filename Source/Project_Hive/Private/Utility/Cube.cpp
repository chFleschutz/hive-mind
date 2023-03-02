// Fill out your copyright notice in the Description page of Project Settings.


#include "Cube.h"


FCube::FCube()
{
}

FCube::FCube(const int32 Q, const int32 R)
{
	M_Q = Q;
	M_R = R;
	M_S = -M_Q - M_R;	//< Make sure Q + R + S = 0
}

FCube::FCube(const FCube& Other)
{
	M_Q = Other.Q();
	M_R = Other.R();
	M_S = Other.S();
}

FCube::FCube(const FCube&& Other)
{
	M_Q = Other.Q();
	M_R = Other.R();
	M_S = Other.S();
}

void FCube::SetQ(const int32 NewQ)
{
	M_Q = NewQ;
	M_S = -M_Q - M_R;	//< Make sure Q + R + S = 0
}

void FCube::SetR(const int32 NewR)
{
	M_R = NewR;
	M_S = -M_Q - M_R;	//< Make sure Q + R + S = 0
}

FCube& FCube::operator=(const FCube& Other)
{
	M_Q = Other.Q();
	M_R = Other.R();
	M_S = Other.S();
	return *this;
}

FCube FCube::operator+(const FCube& Other) const
{
	return FCube(M_Q + Other.Q(), M_R + Other.R());
}

FCube& FCube::operator+=(const FCube& Other)
{
	M_Q += Other.Q();
	M_R += Other.R();
	M_S += Other.S();
	return *this;
}

FCube FCube::operator-(const FCube& Other) const
{
	return FCube(M_Q - Other.Q(), M_R - Other.R());
}

FCube& FCube::operator-=(const FCube& Other)
{
	M_Q -= Other.Q();
	M_R -= Other.R();
	M_S -= Other.S();
	return *this;
}

bool FCube::operator==(const FCube& Other) const
{
	return (M_Q == Other.Q()) && (M_R == Other.R()) && (M_S == Other.S());
}

FCube FCube::Zero()
{
	return FCube(0, 0);
}

float FCube::Distance(const FCube& A, const FCube& B)
{
	const auto Cube = A - B;
	return (abs(Cube.Q()) + abs(Cube.R()) + abs(Cube.S())) / 2;
}

TArray<FCube> FCube::DirectionVectors()
{
	return TArray<FCube>() = { FCube(0, -1), FCube(1, -1), FCube(1, 0), FCube(0, 1), FCube(-1, 1), FCube(-1, 0) };
}

