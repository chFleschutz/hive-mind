// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "World/Tiles/Tile.h"

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Actor.h"
#include "TileStructure.generated.h"

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


// Todo Move later
USTRUCT(BlueprintType)
struct FResource 
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Gold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Wood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Food;
};

/** Data struct of a buildable structure */
USTRUCT(BlueprintType)
struct FStructureData : public FTableRowBase
{
	GENERATED_BODY()
public:
	/** Name of the structure */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
		FText Name;

	/** Icon to use in UI  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Icon"))
		TObjectPtr<UTexture2D> Icon;

	/** Class from which actor will be spawned */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "StructureClass"))
		TObjectPtr<UClass> StructureClass;

	/** Mesh to show in preview */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Mesh"))
		TObjectPtr<UStaticMesh> Mesh;

	/** Valid foundation types to build the structure on */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SupportedFoundationTypes"))
		TArray<EFoundationType> SupportedFoundationTypes;

	/** Resource cost of building the structure */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ResourceCost"))
		FResource ResourceCost;
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
