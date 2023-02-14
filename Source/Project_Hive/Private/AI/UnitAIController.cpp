// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "AI/UnitAIController.h"

#include "AI/NavigableUnit.h"


void AUnitAIController::OnMoveCompleted(const FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (const auto Unit = GetPawn<ANavigableUnit>())
	{
		Unit->OnMoveToTileFinished();
	}
}
