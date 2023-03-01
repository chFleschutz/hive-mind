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


/** Data struct of a hex-tile */
USTRUCT(BlueprintType)
struct FTileData : public FTableRowBase
{
	GENERATED_BODY()
public:
	/** Display Name */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Name"))
		FString Name;

	/** Class to spawn the tile from */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "TileClass", MakeStructureDefaultValue = "None"))
		TObjectPtr<UClass> TileClass;

	/** Foundation type */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "FoundationType", MakeStructureDefaultValue = "FT_Grass"))
		EFoundationType FoundationType;

	/** Name of the vegetation-structure to use */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "VegetationStructure", MakeStructureDefaultValue = "None"))
		FName VegetationStructure;

	/** Name of the mountain-structure to use */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MountainStructure", MakeStructureDefaultValue = "None"))
		FName MountainStructure;

	/** Static Mesh */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Mesh", MakeStructureDefaultValue = "None"))
		TObjectPtr<UStaticMesh> Mesh;

	/** Amount of Vegetation on Tiles */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "VegetationAmount", MakeStructureDefaultValue = "0.000000"))
		double VegetationAmount;

	/** Amount of Mountains on Tiles */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MountainAmount", MakeStructureDefaultValue = "0.000000"))
		double MountainAmount;

	/** Base cost to move on the tile */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BaseTravelCost"))
		int32 BaseTravelCost;
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Icon", MakeStructureDefaultValue = "/Script/Engine.Texture2D'/Game/Assets/Forest/forestThumbnail.forestThumbnail'"))
		TObjectPtr<UTexture2D> Icon;

	/** Class from which actor will be spawned */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "StructureClass", MakeStructureDefaultValue = "None"))
		TObjectPtr<UClass> StructureClass;

	/** Mesh to show in preview */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Mesh", MakeStructureDefaultValue = "None"))
		TObjectPtr<UStaticMesh> Mesh;

	/** Valid foundation types to build the structure on */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SupportedFoundationTypes"))
		TArray<EFoundationType> SupportedFoundationTypes;

	/** Resource cost of building the structure */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ResourceCost", MakeStructureDefaultValue = "(Gold=0,Wood=0,Food=0)"))
		FResource ResourceCost;

	/** Unit types which can be spawned by the structure */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "SpawnableUnitTypes"))
		TArray<FName> SpawnableUnitTypes;

	/** Whether the structure blocks moving on the tile */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BlocksMovement", MakeStructureDefaultValue = "False"))
		bool BlocksMovement;

	/** Travel-cost added by the structure to the tile */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AddedTravelCost"))
		int32 AddedTravelCost;
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

