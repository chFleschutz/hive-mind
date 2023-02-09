// Fill out your copyright notice in the Description page of Project Settings.

#include "World/Tiles/Tile.h"



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

bool ATile::CanBuild(ATileStructure* NewStructure)
{
	if (!IsValid(NewStructure))
		return false;
	if (Structure) // If tile already has a structure
		return false;

	return NewStructure->CheckFoundationSupport(TileFoundationType);
}

void ATile::Build(ATileStructure* NewStructure)
{
	if (!CanBuild(NewStructure))
		return;

	Structure = NewStructure;
	Structure->SetActorLocation(this->GetActorLocation() + FVector(0.0, 0.0, 100.0)); //< Make sure it is in the right spot
	FAttachmentTransformRules rules(EAttachmentRule::KeepWorld, false);
	Structure->AttachToActor(this, rules);
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

	HexTileMesh->SetCollisionObjectType(ECC_GameTraceChannel1);
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

void ATile::addNeighbor(ATile* neighbor)
{
	Neighbors.Emplace(neighbor);
}

