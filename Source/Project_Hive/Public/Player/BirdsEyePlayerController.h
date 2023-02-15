// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BirdsEyePlayerController.generated.h"

class ATile;
class ATileStructure;
class UInputAction;
class UInputComponent;
class UInputMappingContext;
struct FInputActionValue;

/**
 * 
 */
UCLASS()
class PROJECT_HIVE_API ABirdsEyePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable)
		bool HasTileSelected() const;

	UFUNCTION(BlueprintCallable)
		void StartBuildingStructure(TSubclassOf<ATileStructure> Structure);

	UFUNCTION(BlueprintCallable)
		bool CanSpawnCharacter() const;

	UFUNCTION(BlueprintCallable)
		void SpawnUnit(TSubclassOf<class ANavigableUnit> Unit) const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	ATile* QueryTileUnderCursor() const;

	// Input action callbacks:
	//
	void Zoom(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Select(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void MoveToTarget(const FInputActionValue& Value);

	// Input
	//
	/** Mapping Context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	// ReSharper disable once UnrealHeaderToolError
	UInputMappingContext* InputMapping;

	/** Zoom Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* ZoomAction;

	/** Look Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* LookAction;

	/** Move Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* MoveAction;

	/** Select Input Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* SelectAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* MoveTargetAction;


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grid")
		ATile* SelectedTile = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grid")
		ATileStructure* PreviewStructure;
};
