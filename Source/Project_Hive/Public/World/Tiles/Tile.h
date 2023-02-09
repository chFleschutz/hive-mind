// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cube.h"
#include "World/Structures/TileStructure.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class ATileStructure;

UCLASS()
class PROJECT_HIVE_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets the position in the grid
	void setGridPosition(const Cube& position);
	
	void addNeighbor(ATile* neighbor);

	// Renders a highlight outline 
	void SetSelected(bool IsSelected);

	virtual bool CanBuild();

	virtual bool CanBuild(ATileStructure* NewStructure);
	virtual void Build(ATileStructure* NewStructure);
	
	bool CanDestroyBuilding();
	void DestroyBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	// Hexagon Static Mesh Component 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Mesh")
		class UStaticMeshComponent* HexTileMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Tile Settings")
		EFoundationType TileFoundationType;

	ATileStructure* Structure = nullptr;
	
	Cube GridPosition;
	TArray<ATile*> Neighbors;
};
