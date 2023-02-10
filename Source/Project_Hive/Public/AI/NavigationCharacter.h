// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NavigationCharacter.generated.h"

class ATile;

UCLASS()
class PROJECT_HIVE_API ANavigationCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ANavigationCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetStandingTile(ATile* Tile);

	void SetMoveTarget(ATile* TargetTile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement")
		int32 MovementRange = 1;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Movement")
		TArray<ATile*> MovementPath;

private:
	ATile* StandingTile;
};
