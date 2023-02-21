// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TurnBasedGameMode.generated.h"

/** Phases */
UENUM(BlueprintType)
enum class EGamePhase : uint8
{
	GP_Planning		UMETA(DisplayName = "Planning Phase"),
	GP_Executing	UMETA(DisplayName = "Executing Phase"),

	GP_Max			UMETA(Hidden),
};

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

	/**
	 * Signals to wait with switching to planning phase (Use when doing animations, moving, etc)
	 * Meant to be called inside the ExecutionPhaseEvent
	 * Make sure ObjectExecutionFinished is called afterwards
	 */
	void ObjectExecutionStarted();
	/**
	 * Signals that the object finished executing and the phase can continue
	 * Make sure ObjectExecutionStarted was called first
	 * The phase will continue when all objects finished execution
	 */
	void ObjectExecutionFinished();

	DECLARE_EVENT(ATurnBasedGameMode, FPlanningPhaseEvent)
	FPlanningPhaseEvent& OnPlanningPhaseStartedEvent() { return PlanningPhaseEvent; }

	DECLARE_EVENT(ATurnBasedGameMode, FExecutionPhaseEvent)
	FExecutionPhaseEvent& OnExecutionPhaseStartedEvent() { return ExecutionPhaseEvent; }

	EGamePhase GetGamePhase() const { return GamePhase; }

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Game")
		EGamePhase GamePhase = EGamePhase::GP_Planning;

private:
	FPlanningPhaseEvent PlanningPhaseEvent;
	FExecutionPhaseEvent ExecutionPhaseEvent;

	void StartPlanningPhase();
	void StartExecutionPhase();

	int32 NumPlayerReady = 0;
	int32 NumExecuting = 0;
};
