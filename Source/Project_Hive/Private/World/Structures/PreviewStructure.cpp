// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "World/Structures/PreviewStructure.h"


// Sets default values
APreviewStructure::APreviewStructure()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PreviewMesh"));
	MeshComponent->SetupAttachment(RootComponent);
}

void APreviewStructure::SetMesh(UStaticMesh* Mesh) const
{
	MeshComponent->SetStaticMesh(Mesh);
}

void APreviewStructure::SetPreviewState(const bool IsValid) const
{
	auto PreviewMaterial = PreviewRedMaterial;
	if (IsValid)
		PreviewMaterial = PreviewBlueMaterial;

	for (int32 i = 0; i < MeshComponent->GetNumMaterials(); i++)
	{
		MeshComponent->SetMaterial(i, PreviewMaterial);
	}
}

// Called when the game starts or when spawned
void APreviewStructure::BeginPlay()
{
	Super::BeginPlay();

	MeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called every frame
void APreviewStructure::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

