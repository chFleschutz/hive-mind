// Fill out your copyright notice in the Description page of Project Settings.

#include "World/Tiles/GrassTile.h"

#include "World/Structures/TileStructure.h"


bool AGrassTile::CanBuild(ATileStructure* NewStructure)
{
	return static_cast<bool>(!Structure);
}
