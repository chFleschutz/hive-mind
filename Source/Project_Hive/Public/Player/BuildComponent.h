// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "World/Structures/TileStructure.h"
#include "BuildComponent.generated.h"

class APreviewStructure;
class ATile;
class UDataTable;

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECT_HIVE_API UBuildComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuildComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ShowPreview(const FStructureData& StructureData);

	UFUNCTION(BlueprintCallable)
	void HidePreview();

	UFUNCTION(BlueprintCallable)
	bool BuildStructure();

	UFUNCTION(BlueprintCallable)
	bool IsPreviewActive() const { return PreviewStructure != nullptr; }

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		UDataTable* StructuresTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Defaults")
		TSubclassOf<APreviewStructure> PreviewStructureClass;

private:
	void UpdatePreview() const;
	bool IsBuildLocationValid(const ATile* Tile) const;

	UPROPERTY()
	APreviewStructure* PreviewStructure = nullptr;

	FStructureData PreviewData;
	TArray<FStructureData*> BuildableStructures;
};
