// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API AUnitAIController final : public AAIController
{
	GENERATED_BODY()

public:
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

};
