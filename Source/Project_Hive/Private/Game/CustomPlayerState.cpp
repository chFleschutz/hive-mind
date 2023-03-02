// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "CustomPlayerState.h"

bool ACustomPlayerState::CanAfford(const FResource& ResourceCost) const
{
	return ResourceCost <= PlayerResources;
}

void ACustomPlayerState::AddResources(const FResource& Resource)
{
	PlayerResources += Resource;
}

void ACustomPlayerState::RemoveResources(const FResource& Resource)
{
	PlayerResources -= Resource;
}
