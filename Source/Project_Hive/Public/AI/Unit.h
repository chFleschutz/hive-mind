// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "World/Tiles/Tile.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Unit.generated.h"


UCLASS()
class PROJECT_HIVE_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnPlanningPhaseStarted();
	virtual void OnExecutionPhaseStarted();

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
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		int32 MovementRange = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		TArray<EFoundationType> UnitMoveTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		TArray<ATile*> MovementPath;

private:
	UPROPERTY(VisibleInstanceOnly, Category = "Movement")
		ATile* StandingTile;

	UPROPERTY(VisibleInstanceOnly, Category = "Movement")
		bool IsMoving = false;

	void MoveToTile(ATile* NextTile);
};
