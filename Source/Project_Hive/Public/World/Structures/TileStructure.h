// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once


#include "CoreMinimal.h"
#include "Utility/DataStructs.h"
#include "GameFramework/Actor.h"
#include "TileStructure.generated.h"

class ATile;

/** Current state of the structure */
UENUM(BlueprintType)
enum class EStructureState : uint8
{
	Planning,
	Construction,
	Ready,
	Demolish,

	Max		UMETA(Hidden),
};

UCLASS()
class PROJECT_HIVE_API ATileStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileStructure();

	void SetTile(ATile* Tile) { FoundationTile = Tile; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetStructureData(FStructureData Data);

	void DisplayInfo(bool IsVisible);

	virtual bool CheckFoundationSupport(EFoundationType Foundation) const;

	virtual bool BlocksUnitMovement() const { return StructureData.BlocksMovement; }

	virtual int32 AddedTravelCost() const { return StructureData.AddedTravelCost; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FStructureData GetData() const { return StructureData; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	// Determines the supported foundations this structure can be build on
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Defaults")
		int32 ConstructionTime;

	/** Hex Static Mesh Component */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Defaults")
		UStaticMeshComponent* TileStructureMesh;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Structure")
		EStructureState State = EStructureState::Planning;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		FStructureData StructureData;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly)
		ATile* FoundationTile;
};
