// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BirdsEyePlayerController.generated.h"

class ATile;
class ATileStructure;
class UBuildComponent;
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
	ABirdsEyePlayerController();

	UFUNCTION(BlueprintCallable)
		bool HasTileSelected() const;

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void BuildStructure(int32 StructureID);

	UFUNCTION(BlueprintCallable)
		void ToggleBuildMode(bool IsActive) const;

	UFUNCTION(BlueprintCallable)
		bool CanSpawnCharacter() const;

	UFUNCTION(BlueprintCallable)
		void SpawnUnit(TSubclassOf<class ANavigableUnit> Unit) const;

	ATile* QueryTileUnderCursor() const;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;

	// Input action callbacks:
	//
	void Zoom(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Select(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void MoveToTarget(const FInputActionValue& Value);

	// Components
	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
		TSubclassOf<UBuildComponent> BuildComponentClass;

	// Input
	//
	/** Default Mapping Context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* DefaultMapping;
	/** Select Mapping Context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* SelectMapping;
	/** Build mode Mapping Context */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
		UInputMappingContext* BuildModeMapping;

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
	/** Move to Target-location Action*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* MoveTargetAction;
	/** Apply Building Structure Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* BuildApplyAction;
	/** Abort Building Structure Action */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input|Actions")
		UInputAction* BuildAbortAction;


	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grid")
		ATile* SelectedTile = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Grid")
		ATileStructure* PreviewStructure;

private:
	UPROPERTY(VisibleInstanceOnly)
	class UBuildComponent* BuildComponent;

};
