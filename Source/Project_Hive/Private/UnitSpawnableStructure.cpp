// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "UnitSpawnableStructure.h"

#include "AI/Unit.h"

void AUnitSpawnableStructure::StartCreatingUnit(const FUnitData& UnitData)
{
	if (CreationQueue.Num() == MaxQueueSize)
		return;

	CreationQueue.Emplace(FUnitCreationInfo{ UnitData,UnitData.CreationTime });
}

TArray<FUnitCreationInfo> AUnitSpawnableStructure::GetSpawnQueue()
{
	return CreationQueue;
}

void AUnitSpawnableStructure::OnExecutionPhaseStarted()
{
	Super::OnExecutionPhaseStarted();

	const auto FilterQueue = [this](const FUnitCreationInfo& Info)
	{
		if (Info.TurnsRemaining == 0)
		{
			SpawnUnit(Info.UnitData.UnitClass);
			return true;
		}
		return false;
	};
	CreationQueue.RemoveAll(FilterQueue);

	for (auto& Item : CreationQueue)
	{
		Item.TurnsRemaining--;
	}
}

void AUnitSpawnableStructure::SpawnUnit(const TSubclassOf<AUnit> UnitClass) const
{
	if (const auto World = GetWorld())
	{
		if (!IsValid(UnitClass))
			return;

		const auto Location = GetActorLocation();
		const auto Rotation = GetActorRotation();
		FActorSpawnParameters Parameters;
		Parameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		if (const auto NewUnit = World->SpawnActor<AUnit>(UnitClass, Location, Rotation, Parameters))
		{
			// Todo: set unit on Tile
		}
	}
}
