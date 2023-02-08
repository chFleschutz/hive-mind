// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "World/Tiles/Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGrid.generated.h"

class Cube;

UCLASS()
class PROJECT_HIVE_API AHexGrid : public AActor
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
		void RandomSeed();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void GenerateCircle();

	// Returns the world-location for the grid coordinate
	FVector WorldLocation(const Cube& gridPosition);
	// Spawn a Tile at gridPosition 
	void SpawnTile(const Cube& gridPosition, TSubclassOf<ATile> tileToSpawn);

	// Returns a tile based on value
	TSubclassOf<ATile> GetTileFor(const Cube& gridPos, float value);

	FVector GridOrigin;
	TArray<ATile*> GeneratedTiles;

protected:
	// Grid Layout Settings
	//
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout")
		int32 GridSize = 3;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout")
		double GridCellSize = 100.0;

	// Random Generation Settings
	//
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		bool AutoGenerateRandomSeed = true;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		int32 Seed = 0x00000000;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		int32 NoiseCellSize = 10;
	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float SandValue = 0.5f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float WaterValue = 0.5f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Layout|Random")
		float GrassValue = 1.0f;

	// Tiles
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout|Tiles")
		TSubclassOf<ATile> GrassTile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout|Tiles")
		TSubclassOf<ATile> SandTile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Layout|Tiles")
		TSubclassOf<ATile> WaterTile;
};
