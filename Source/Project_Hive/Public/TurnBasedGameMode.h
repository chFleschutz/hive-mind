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

	DECLARE_EVENT(ATurnBasedGameMode, FPlanningPhaseEvent)
	FPlanningPhaseEvent& OnPlanningPhaseStarted() { return PlanningPhaseEvent; }

	DECLARE_EVENT(ATurnBasedGameMode, FExecutionPhaseEvent)
	FExecutionPhaseEvent& OnExecutionPhaseStarted() { return ExecutionPhaseEvent; }

private:
	FPlanningPhaseEvent PlanningPhaseEvent;
	FExecutionPhaseEvent ExecutionPhaseEvent;

	void ExecutePlayerTurns();

	int32 NumPlayerReady = 0;
};
