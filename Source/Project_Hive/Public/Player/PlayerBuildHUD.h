// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerBuildHUD.generated.h"

/**
 * 
 */

class UUserWidget;

UCLASS()
class PROJECT_HIVE_API APlayerBuildHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, Category = "Build")
		TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
		class UUserWidget* CurrentWidget;
};
