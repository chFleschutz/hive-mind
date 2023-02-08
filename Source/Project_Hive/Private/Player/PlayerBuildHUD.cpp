// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBuildHUD.h"

#include "Blueprint/UserWidget.h"

void APlayerBuildHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!HUDWidgetClass)
		return;

	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	if (CurrentWidget)
		CurrentWidget->AddToViewport();
}

