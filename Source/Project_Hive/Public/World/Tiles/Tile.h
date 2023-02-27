// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "Cube.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

class AUnit;
class ATileStructure;
class ATileVegetation;

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
	void SetGridPosition(const FCube& Position);
	// Returns the position in the grid
	FCube GetGridPosition() { return GridPosition; }

	// Adds a neighbor of this tile
	void AddNeighbor(ATile* Neighbor);
	// Returns all neighbors of this tile
	TArray<ATile*> GetNeighbors() { return Neighbors; }

	// Renders a highlight outline 
	void SetSelected(bool IsSelected);
	bool GetIsSelected() const { return IsTileSelected; }
	void ShowHighlight(bool IsHighlighted) const;

	virtual bool CanBuild(ATileStructure* NewStructure);
	UFUNCTION(BlueprintCallable)
	virtual void Build(ATileStructure* NewStructure);
	
	bool CanDestroyBuilding() const;
	void DestroyBuilding();

	// Returns the Structure on the Tile (May returns nullptr);
	ATileStructure* GetStructure() const { return Structure; }

	virtual bool CanPlaceUnit();
	bool PlaceUnit(AUnit* Unit);
	AUnit* GetUnit() const { return PlacedUnit; }
	void RemoveUnit();

	UFUNCTION(BlueprintCallable)
	FVector GetCenterSocketLocation() const { return CenterSocket->GetComponentLocation(); }

	UFUNCTION(BlueprintCallable, BlueprintGetter)
	EFoundationType GetType() const { return TileFoundationType; }

	void BuildVegetation();
	void BuildMountain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	// Hexagon Static Mesh Component 
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		UStaticMeshComponent* HexTileMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components")
		USceneComponent* CenterSocket;

	// Tile Settings
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tile Settings")
		TSubclassOf<ATileVegetation> VegetationType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tile Settings")
		TSubclassOf<ATileVegetation> MountainType;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Tile Settings")
		EFoundationType TileFoundationType;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Tile Settings")
		ATileStructure* Structure = nullptr;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Tile Settings")
		AUnit* PlacedUnit = nullptr;

private:
	void AppendStructure(ATileStructure* NewStructure);
	void BuildStructure(TSubclassOf<ATileStructure> StructureType);

	void QueryTilesInMovementRange();
	void DisplayMovementRange(bool IsVisible);

	bool IsTileSelected = false;
	FCube GridPosition;
	TArray<ATile*> Neighbors;
	TArray<ATile*> TilesInMovementRange;
};
