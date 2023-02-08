// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileStructure.generated.h"

UCLASS()
class PROJECT_HIVE_API ATileStructure : public AActor
{
	GENERATED_BODY()
	
public:	

	// Sets default values for this actor's properties
	ATileStructure();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Components
	//
	/** Hex Static Mesh Component */
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Mesh")
		class UStaticMeshComponent* tileStructureMesh;
};
