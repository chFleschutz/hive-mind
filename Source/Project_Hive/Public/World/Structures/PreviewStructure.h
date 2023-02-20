// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PreviewStructure.generated.h"

UCLASS()
class PROJECT_HIVE_API APreviewStructure : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APreviewStructure();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMesh(UStaticMesh* Mesh) const;
	void SetPreviewState(bool IsValid) const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		UMaterial* PreviewBlueMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		UMaterial* PreviewRedMaterial;

private:
	UPROPERTY()
	UStaticMeshComponent* MeshComponent;
};
