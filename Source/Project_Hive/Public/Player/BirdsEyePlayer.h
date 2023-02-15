// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "BirdsEyePlayer.generated.h"

class ATile;
class ATileStructure;
class UInputAction;
class UInputComponent;
class UInputMappingContext;
class UStaticMeshComponent;
struct FInputActionValue;

UCLASS()
class PROJECT_HIVE_API ABirdsEyePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABirdsEyePlayer();

	void AddZoomInput(float Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	/** An invisible Mesh Component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Mesh")
		UStaticMeshComponent* InvisibleMesh;
	
	/** Camera Component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Camera")
		class UCameraComponent* Camera;

	/** Spring Arm Component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Components|Camera")
		class USpringArmComponent* SpringArm;

	/** DefaultPawn movement component */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Pawn")
		class UFloatingPawnMovement* MovementComponent;

	// Camera Settings
	//
	/** Min Length of Spring Arm */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings")
		float MinCameraZoom = 500.0f;

	/** Max Length of Spring Arm */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings")
		float MaxCameraZoom = 2000.0f;

	/** Zoom Speed */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Player Settings")
		float ZoomSpeed = 100.0f;

	/** Min Pitch Angle */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Settings")
		float MinPitchAngle = 290.0f;

	/** Max Pitch Angle */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Settings")
		float MaxPitchAngle = 360.0f;
};
