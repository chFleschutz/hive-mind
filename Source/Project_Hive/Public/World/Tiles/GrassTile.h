// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GrassTile.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API AGrassTile : public ATile
{
	GENERATED_BODY()
	
public:
	AGrassTile() = default;

	virtual bool CanBuild(ATileStructure* NewStructure) override;
};
