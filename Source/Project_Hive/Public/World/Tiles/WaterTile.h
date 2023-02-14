// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "WaterTile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API AWaterTile : public ATile
{
	GENERATED_BODY()
	
public:
	virtual bool CanBuild(ATileStructure* NewStructure) override;
};
