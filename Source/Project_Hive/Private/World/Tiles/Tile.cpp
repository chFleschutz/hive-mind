// Fill out your copyright notice in the Description page of Project Settings.

#include "World/Tiles/Tile.h"

#include "World/Structures/TileStructure.h"


// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));

	HexTileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	HexTileMesh->SetupAttachment(RootComponent);
}

void ATile::SetSelected(bool IsSelected)
{
	if (HexTileMesh)
	{
		HexTileMesh->SetRenderCustomDepth(IsSelected);
	}
}

bool ATile::CanBuild()
{
	return static_cast<bool>(!Structure);
}

bool ATile::CanDestroyBuilding()
{
	return static_cast<bool>(Structure);
}

void ATile::Build(TSubclassOf<ATileStructure> structure)
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

void ATile::DestroyBuilding()
{
	if (Structure)
	{
		Structure->Destroy();
		Structure = nullptr;
	}
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::setGridPosition(const Cube& position)
{
	GridPosition = position;
}

