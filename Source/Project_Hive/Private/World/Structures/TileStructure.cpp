// Fill out your copyright notice in the Description page of Project Settings.


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
	
}

// Called every frame
void ATileStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ATileStructure::CheckFoundationSupport(EFoundationType Foundation)
{
	return SupportedFoundationTypes.Contains(Foundation);
}
