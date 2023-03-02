// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Utility/DataStructs.h"
#include "GameFramework/Character.h"
#include "Unit.generated.h"

class ATile;
class UWidgetComponent;

UCLASS()
class PROJECT_HIVE_API AUnit : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUnit();

	void Initialize(const FUnitData& Data);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	virtual void OnPlanningPhaseStarted();

	UFUNCTION()
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

	void MoveToTile(ATile* NextTile);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		FUnitData UnitData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		UWidgetComponent* HealthWidgetComponent;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		TArray<ATile*> MovementPath;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		int32 MovementRange;

	UPROPERTY(VisibleInstanceOnly, Category = "Movement")
		ATile* StandingTile;

	UPROPERTY(VisibleInstanceOnly, Category = "Movement")
		bool IsMoving = false;

	UPROPERTY(VisibleInstanceOnly, Category = "Combat")
		float CurrentHealth;
};
