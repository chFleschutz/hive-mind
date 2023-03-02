// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Resource.h"
#include "GameFramework/PlayerState.h"
#include "CustomPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API ACustomPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	/**
	 * @brief Determines if player can afford ResourceCost
	 * @param ResourceCost Resources to compare the player resources to
	 * @return true if player has equal or more than ResourceCost
	 */
	bool CanAfford(const FResource& ResourceCost) const;

	/**
	 * @brief Adds Resource to PlayerResources
	 * @param Resource Amount to add to PlayerResources
	 */
	void AddResources(const FResource& Resource);

	/**
	 * @brief Removes Resource from PlayerResources
	 * @param Resource Amount to remove from PlayerResources
	 * @note Make sure CanAfford returns true before calling this
	 */
	void RemoveResources(const FResource& Resource);

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
		FResource PlayerResources;
};
