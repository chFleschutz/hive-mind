// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataStructs.h"
#include "World/Structures/TurnControlledStructure.h"
#include "UnitSpawnableStructure.generated.h"

USTRUCT(BlueprintType)
struct FUnitCreationInfo
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		TSubclassOf<class AUnit> UnitClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 TurnsRemaining;
};

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API AUnitSpawnableStructure : public ATurnControlledStructure
{
	GENERATED_BODY()

public:
	// show info on hud

	// create unit
	UFUNCTION(BlueprintCallable)
	void StartCreatingUnit(const FUnitData& UnitData);

	virtual void OnExecutionPhaseStarted() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
		int32 MaxQueueSize = 3;

private:
	void SpawnUnit(TSubclassOf<AUnit> UnitClass) const;

	TArray<FUnitCreationInfo> CreationQueue;
};
