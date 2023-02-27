// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "UObject/NoExportTypes.h"
#include "DataStructs.generated.h"

/** Resources to buy things */
USTRUCT(BlueprintType)
struct FResource
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Gold;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Wood;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Food;
};


/** Foundation types of tiles */
UENUM(BlueprintType)
enum class EFoundationType : uint8
{
	FT_Grass	UMETA(DisplayName = "Grass"),
	FT_Sand		UMETA(DisplayName = "Sand"),
	FT_Water	UMETA(DisplayName = "Water"),

	FT_Max		UMETA(Hidden),
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

	/** Unit types which can be spawned by the structure */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SpawnableUnitTypes"))
		TArray<FName> SpawnableUnitTypes;
};



/** Please add a struct description */
USTRUCT(BlueprintType)
struct FUnitData : public FTableRowBase
{
	GENERATED_BODY()
public:
	/** Display Name */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
		FText Name;

	/** Display Icon */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Icon", MakeStructureDefaultValue = "None"))
		TObjectPtr<UTexture2D> Icon;

	/** Class the Unit will be spawned from */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "UnitClass", MakeStructureDefaultValue = "None"))
		TObjectPtr<UClass> UnitClass;

	/** Number of rounds required to spawn */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "CreationTime", MakeStructureDefaultValue = "0"))
		int32 CreationTime;

	/** Cost to create  */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cost", MakeStructureDefaultValue = "(Gold=0,Wood=0,Food=0)"))
		FResource Cost;
};

