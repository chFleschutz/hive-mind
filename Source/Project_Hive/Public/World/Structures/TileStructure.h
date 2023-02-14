// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "World/Tiles/Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileStructure.generated.h"

UCLASS()
class PROJECT_HIVE_API ATileStructure : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ATileStructure();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool CheckFoundationSupport(EFoundationType Foundation) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	/** Hex Static Mesh Component */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Structure|Mesh")
		class UStaticMeshComponent* TileStructureMesh;

	// Determines the supported foundations this structure can be build on
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Structure")
		TArray<EFoundationType> SupportedFoundationTypes;
};
