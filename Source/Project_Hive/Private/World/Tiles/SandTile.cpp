// Fill out your copyright notice in the Description page of Project Settings.


#include "World/Tiles/SandTile.h"


bool ASandTile::CanBuild()
{
    return false;
}

void ASandTile::Build(TSubclassOf<ATileStructure> structure)
{
}
