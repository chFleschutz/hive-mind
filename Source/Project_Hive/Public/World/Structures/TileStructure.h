// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "World/Tiles/Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileStructure.generated.h"

/** Foundation types of tiles */
UENUM(BlueprintType)
enum class EStructureState : uint8
{
	Planning,
	Construction,
	Ready,
	Demolish,

	FT_Max		UMETA(Hidden),
};


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

	virtual bool BlocksUnitMovement() const { return false; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	/** Hex Static Mesh Component */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Defaults")
		class UStaticMeshComponent* TileStructureMesh;

	// Determines the supported foundations this structure can be build on
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Defaults")
		TArray<EFoundationType> SupportedFoundationTypes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
		int32 ConstructionTime;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Structure")
		EStructureState State = EStructureState::Planning;
};
