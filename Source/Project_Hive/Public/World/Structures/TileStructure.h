// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileStructure.generated.h"

/** Foundation type of tiles */
UENUM(BlueprintType)
enum class EFoundationType : uint8
{
	FT_Grass	UMETA(DisplayName = "Grass"),
	FT_Sand		UMETA(DisplayName = "Sand"),
	FT_Water	UMETA(DisplayName = "Water"),

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

	bool CheckFoundationSupport(EFoundationType Foundation);

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
