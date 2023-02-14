// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "World/Tiles/Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"

class FCube;

UCLASS()
class PROJECT_HIVE_API AHexGrid final : public AActor
{
	GENERATED_BODY()
public:	
	// Sets default values for this actor's properties
	AHexGrid();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor, Category = "Layout")
		void Generate();

	UFUNCTION(CallInEditor, Category = "Layout")
		void DestroyTiles();

	UFUNCTION(CallInEditor, Category = "Layout")
		void RandomizeSeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Grid Layout Settings
	//
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout")
		int32 GridSize = 10;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout")
		double GridCellSize = 100.0;

	// Random Generation Settings
	//
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		bool AutoGenerateRandomSeed = true;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		int32 Seed = 0x00000000;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		int32 NoiseCellSize = 5;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float SandValue = 0.5f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float WaterValue = 0.5f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float GrassValue = 1.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float ForestAmount = 0.4f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float DesertVegetationAmount = 0.1f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float MountainAmount = 0.05f;

	// Tiles
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout|Tiles")
		TSubclassOf<ATile> GrassTile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout|Tiles")
		TSubclassOf<ATile> SandTile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout|Tiles")
		TSubclassOf<ATile> WaterTile;

private:
	void GenerateCircle();
	// Returns the world-location for the grid coordinate
	FVector WorldLocation(const FCube& GridPosition) const;
	// Spawn a Tile at gridPosition 
	ATile* SpawnTile(const FCube& GridPosition, TSubclassOf<ATile> TileToSpawn);
	// Returns a tile based on value
	TSubclassOf<ATile> GetTileFor(const FCube& GridPos, float Value) const;
	void SpawnTileAt(const FCube& GridPos, float Value);
	void SetAllNeighbors();
	
	// ReSharper disable once CppUE4ProbableMemoryIssuesWithUObjectsInContainer because FCube is not a UClass
	TMap<FCube, ATile*> Grid;

	FVector GridOrigin;
};
