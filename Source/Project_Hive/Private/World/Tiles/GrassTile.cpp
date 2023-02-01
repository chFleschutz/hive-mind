// Fill out your copyright notice in the Description page of Project Settings.

#include "World/Tiles/GrassTile.h"

#include "World/Structures/TileStructure.h"


bool AGrassTile::CanBuild()
{
	return static_cast<bool>(!Structure);
}

void AGrassTile::Build(TSubclassOf<ATileStructure> structure)
{
	if (Structure)
		return;

	if (!IsValid(structure))
		return;

	auto world = GetWorld();
	if (!IsValid(world))
		return;

	auto Location = FVector(0.0, 0.0, 100.0);
	auto Rotation = FRotator(0.0, 60.0 * FMath::RandRange(0, 5), 0.0);
	auto NewStructure = world->SpawnActor<ATileStructure>(structure, Location, Rotation);

	if (IsValid(NewStructure))
	{
		Structure = NewStructure;
		FAttachmentTransformRules rules(EAttachmentRule::KeepRelative, false);
		NewStructure->AttachToActor(this, rules);
	}
}
