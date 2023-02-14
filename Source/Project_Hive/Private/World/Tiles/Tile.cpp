// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#include "World/Tiles/Tile.h"

#include "AI/NavigableUnit.h"
#include "World/Structures/TileStructure.h"
#include "World/Structures/TileVegetation.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRootComponent"));

	HexTileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tile"));
	HexTileMesh->SetupAttachment(RootComponent);

	CenterSocket = CreateDefaultSubobject<USceneComponent>(TEXT("Center Socket"));
	CenterSocket->SetupAttachment((HexTileMesh));
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

void ATile::SetSelected(const bool IsSelected)
{
	if (HexTileMesh)
	{
		IsTileSelected = IsSelected;
		HexTileMesh->SetRenderCustomDepth(IsSelected);
	}
}

void ATile::SetNeighborsSelected(const bool IsSelected, const int32 Depth) 
{
	if (Depth <= 0)
		return;

	for (const auto Neighbor : Neighbors)
	{
		if (Neighbor->GetIsSelected() == IsSelected)
			continue;

		Neighbor->SetSelected(IsSelected);
		Neighbor->SetNeighborsSelected(IsSelected, Depth - 1);
	}
}

bool ATile::CanDestroyBuilding() const
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

	AppendStructure(NewStructure);
}

void ATile::DestroyBuilding()
{
	if (Structure)
	{
		Structure->Destroy();
		Structure = nullptr;
	}
}

bool ATile::CanPlaceUnit()
{
	return !PlacedUnit;
}

bool ATile::PlaceUnit(ANavigableUnit* Unit)
{
	if (!CanPlaceUnit())
		return false;

	PlacedUnit = Unit;
	return true;
}

void ATile::BuildVegetation()
{
	//if (!VegetationType)
	//	return;

	//if (Structure)
	//	return;

	//if(const auto World = GetWorld())
	//{
	//	const auto Location = CenterSocket->GetComponentLocation();
	//	const auto Rotation = FRotator(0.0, 60.0 * FMath::RandRange(0, 5), 0.0);
	//	const auto Vegetation = World->SpawnActor<ATileStructure>(VegetationType, Location, Rotation);
	//	AppendStructure(Vegetation);
	//}
	BuildStructure(VegetationType);
}

void ATile::BuildMountain()
{
	BuildStructure(MountainType);
}

void ATile::SetGridPosition(const FCube& Position)
{
	GridPosition = Position;
}

void ATile::AddNeighbor(ATile* Neighbor)
{
	Neighbors.Emplace(Neighbor);
}

void ATile::AppendStructure(ATileStructure* NewStructure)
{
	Structure = NewStructure;
	Structure->SetActorLocation(CenterSocket->GetComponentLocation());
	const FAttachmentTransformRules Rules(EAttachmentRule::KeepWorld, false);
	Structure->AttachToActor(this, Rules);
}

void ATile::BuildStructure(const TSubclassOf<ATileStructure> StructureType)
{
	if (!IsValid(StructureType))
		return;

	if (Structure)
		return;

	if (const auto World = GetWorld())
	{
		const auto Location = CenterSocket->GetComponentLocation();
		const auto Rotation = FRotator(0.0, 60.0 * FMath::RandRange(0, 5), 0.0);
		const auto NewStructure = World->SpawnActor<ATileStructure>(StructureType, Location, Rotation);
		AppendStructure(NewStructure);
	}
}