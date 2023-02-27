// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AStarNavigation.generated.h"

class ATile;
class AUnit;

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API UAStarNavigation final : public UObject
{
	GENERATED_BODY()

public:
	/**
	 *	@brief Finds the shortest Path from StartTile to GoalTile using AStart-Path-finding
	 *	@param StartTile The tile where the path starts
	 *	@param GoalTile The tile where the path should end
	 *	@param Unit The unit following the path (important to determine which tiles best to use)
	 *	@return Array with all tiles on the shortest path from StartTile to GoalTile (excluding StartTile)
	 *	@note The returned Array is empty if no path between StartTile and GoalTile could be found
	 *	@note The returned Array is ordered with the last tile being the GoalTile
	 */
	static TArray<ATile*> GetPath(ATile* StartTile, ATile* GoalTile, AUnit* Unit);

private:
	// Returns a value depending on how far CurrentTile is away from GoalTile
	static float Heuristic(ATile* CurrentTile, ATile* GoalTile);

	// Returns the cost of traveling from StartTile to NextTile
	static int32 TravelCost(ATile* StartTile, ATile* NextTile);
};
