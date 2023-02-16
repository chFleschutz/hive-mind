// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#include "World/Structures/TileStructure.h"


// Sets default values
ATileStructure::ATileStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Root Component"));

	TileStructureMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile Structure Mesh"));
	TileStructureMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATileStructure::BeginPlay()
{
	Super::BeginPlay();

	TileStructureMesh->SetCollisionObjectType(ECC_GameTraceChannel2);
	State = EStructureState::Planning;
}

// Called every frame
void ATileStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATileStructure::CheckFoundationSupport(const EFoundationType Foundation) const
{
	return SupportedFoundationTypes.Contains(Foundation);
}
