// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "World/Tiles/Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NavigableUnit.generated.h"

class ATile;

UCLASS()
class PROJECT_HIVE_API ANavigableUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANavigableUnit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void SetStandingTile(ATile* Tile);

	virtual bool CanMoveTo(ATile* Tile);

	void SetMoveTarget(ATile* TargetTile);
	void StartMoveToTarget();

	void MoveToNextTileOnPath();
	void OnMoveToTileFinished();

	int32 GetMovementRange() const { return MovementRange; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		int32 MovementRange = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		EFoundationType UnitType;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		TArray<ATile*> MovementPath;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Movement")
		ATile* StandingTile;

	UPROPERTY(VisibleInstanceOnly, Category = "Movement")
		bool IsMoving = false;

	void MoveToTile(ATile* NextTile);
};
