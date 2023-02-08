// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BirdsEyePlayer.generated.h"

class UInputComponent;
class ATile;
class ATileStructure;
struct FInputActionValue;

UCLASS()
class PROJECT_HIVE_API ABirdsEyePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdsEyePlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void BuildOnSelectedTile();

	UFUNCTION(BlueprintCallable)
		void DestroyBuildingOnSelectedTile();

	UFUNCTION(BlueprintCallable)
		bool CanBuild();

	UFUNCTION(BlueprintCallable)
		bool CanDestroyBuilding();

	UFUNCTION(BlueprintCallable)
		bool HasTileSelected();

	UFUNCTION(BlueprintCallable)
		void startBuildingStructure(TSubclassOf<ATileStructure> structure);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Input action callbacks:
	//
	void Zoom(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Move(const FInputActionValue& Value);
	void Select(const FInputActionValue& Value);

public:
	// Components
	//
	/** An invisible Mesh Component */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Components|Mesh", meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* InvisibleMesh;
	
	/** Camera Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera", meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* Camera;

	/** Spring Arm Component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components|Camera", meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* SpringArm;

	/** DefaultPawn movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pawn, meta = (AllowPrivateAccess = "true"))
		class UFloatingPawnMovement* MovementComponent;

	// Camera Settings
	//
	/** Min Length of Spring Arm */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings", meta = (AllowPrivateAccess = "true"))
		float MinCameraZoom = 500.0f;

	/** Max Length of Spring Arm */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings", meta = (AllowPrivateAccess = "true"))
		float MaxCameraZoom = 2000.0f;

	/** Zoom Speed */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings", meta = (AllowPrivateAccess = "true"))
		float ZoomSpeed = 100.0f;

	/** Min Pitch Angle */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Settings", meta = (AllowPrivateAccess = "true"))
		float MinPitchAngle = 300.0f;

	/** Max Pitch Angle */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Settings", meta = (AllowPrivateAccess = "true"))
		float MaxPitchAngle = 360.0f;

	// Gameplay
	//
	/** Default Build Structure */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Structure")
		TSubclassOf<ATileStructure> DefaultStructure;

	// Input
	//
	/** Mapping Context */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
		class UInputMappingContext* InputMapping;

	/** Zoom Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
		class UInputAction* ZoomAction;

	/** Look Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
		class UInputAction* LookAction;

	/** Move Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
		class UInputAction* MoveAction;

	/** Select Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input|Actions", meta = (AllowPrivateAccess = "true"))
		class UInputAction* SelectAction;

private:
	ATile* QueryTileUnderCursor();

	// Members
	ATile* SelectedTile = nullptr;

	ATileStructure* PreviewStructure;
};
