// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AStarNavigation.h"

#include "World/Tiles/Tile.h"
#include "Utility/PriorityQueue.h"

TArray<ATile*> UAStarNavigation::GetPath(ATile* StartTile, ATile* GoalTile)
{
	TPriorityQueue<ATile*> Frontier;
	Frontier.Push(StartTile, 0);

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
			const auto NewCost = CostUntilTile[CurrentTile] + 1; 	// TODO: Add cost to tiles
			if (!CostUntilTile.Contains(NextTile) || NewCost < CostUntilTile[NextTile])
			{
				CostUntilTile.Emplace(NextTile, NewCost);
				const auto Priority = NewCost + Heuristic(NextTile, GoalTile);
				Frontier.Push(NextTile, Priority);
				CameFromTile.Emplace(NextTile, CurrentTile);
			}
		}
	}

	// Query best path
	TArray<ATile*> Path;
	auto CurrentTile = GoalTile;
	while (CurrentTile != StartTile)
	{
		Path.Insert(CurrentTile, 0);
		CurrentTile = CameFromTile[CurrentTile];
	}
	return Path;
}

float UAStarNavigation::Heuristic(ATile* StartTile, ATile* GoalTile)
{
	return FCube::Distance(StartTile->GetGridPosition(), GoalTile->GetGridPosition());
}
