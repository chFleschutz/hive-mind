// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#include "AI/AStarNavigation.h"

#include "World/Tiles/Tile.h"
#include "AI/NavigableUnit.h"
#include "Utility/PriorityQueue.h"


TArray<ATile*> UAStarNavigation::GetPath(ATile* StartTile, ATile* GoalTile, ANavigableUnit* Unit)
{
	TPriorityQueue<ATile*> Frontier;
	Frontier.Push(StartTile, 0.0f);

	TMap<ATile*, ATile*> CameFromTile;
	CameFromTile.Add(StartTile, nullptr);

	TMap<ATile*, int32> CostUntilTile;
	CostUntilTile.Add(StartTile, 0);

	while (!Frontier.IsEmpty())
	{
		const auto CurrentTile = Frontier.Pop();

		if (CurrentTile == GoalTile) //< Early out
			break;

		for (const auto NextTile : CurrentTile->GetNeighbors())
		{
			if (!Unit->CanMoveTo(NextTile)) //< Skip impossible tiles
				continue;

			const auto NewCost = CostUntilTile[CurrentTile] + TravelCost(CurrentTile, NextTile); 
			if (!CostUntilTile.Contains(NextTile) || NewCost < CostUntilTile[NextTile])
			{
				CostUntilTile.Emplace(NextTile, NewCost);
				const auto Priority = NewCost + Heuristic(NextTile, GoalTile);
				Frontier.Push(NextTile, Priority);
				CameFromTile.Emplace(NextTile, CurrentTile);
			}
		}
	}

	// Retrieve best path
	if (!CameFromTile.Contains(GoalTile))
		return TArray<ATile*>();

	TArray<ATile*> Path;
	auto CurrentTile = GoalTile;
	while (CurrentTile != StartTile)
	{
		Path.Insert(CurrentTile, 0);
		CurrentTile = CameFromTile[CurrentTile];
	}
	return Path;
}

float UAStarNavigation::Heuristic(ATile* CurrentTile, ATile* GoalTile)
{
	return FCube::Distance(CurrentTile->GetGridPosition(), GoalTile->GetGridPosition());
}

int32 UAStarNavigation::TravelCost(ATile* StartTile, ATile* NextTile)
{
	// TODO: Get Travel cost between Tiles
	
	return 1;
}
