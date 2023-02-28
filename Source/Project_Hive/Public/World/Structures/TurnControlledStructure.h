// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "World/Structures/TileStructure.h"
#include "TurnControlledStructure.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API ATurnControlledStructure : public ATileStructure
{
	GENERATED_BODY()

public:
	// Overridable event called when planning phase was started by game-mode
	UFUNCTION()
	virtual void OnPlanningPhaseStarted() {}
	// Overridable event called when execution phase was started by game-mode
	UFUNCTION()
	virtual void OnExecutionPhaseStarted() {}

protected:
	virtual void BeginPlay() override;
};
