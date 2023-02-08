// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cube.h"

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

	// Renders a highlight outline 
	void SetSelected(bool IsSelected);

	virtual bool CanBuild();
	void Build(ATileStructure* structure);
	
	bool CanDestroyBuilding();
	void DestroyBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Components
	//
	// Hexagon Static Mesh Component 
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Components|Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* HexTileMesh;

protected:
	ATileStructure* Structure = nullptr;
	Cube GridPosition;
};
