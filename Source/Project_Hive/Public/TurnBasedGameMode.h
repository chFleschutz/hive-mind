// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurnBasedGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API ATurnBasedGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATurnBasedGameMode();

	UFUNCTION(BlueprintCallable)
	void PlayerFinishedTurn();

private:
	void ExecutePlayerTurns();

	int32 NumPlayerReady = 0;
};
