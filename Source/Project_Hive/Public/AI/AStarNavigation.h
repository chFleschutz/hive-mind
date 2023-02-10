// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AStarNavigation.generated.h"

class ATile;

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API UAStarNavigation : public UObject
{
	GENERATED_BODY()

public:
	static TArray<ATile*> GetPath(ATile* StartTile, ATile* GoalTile);

private:
	static float Heuristic(ATile* StartTile, ATile* GoalTile);
};
