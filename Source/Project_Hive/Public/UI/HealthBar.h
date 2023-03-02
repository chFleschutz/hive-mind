// Copyright 2023 Christoph Fleschutz. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

class UProgressBar;
class UTextBlock;

/**
 * 
 */
UCLASS(Abstract)
class PROJECT_HIVE_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetMaxHealth(float NewMaxHealth);
	void SetCurrentHealth(float NewCurrentHealth);

protected:
	void UpdateHealthBar() const;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentHealthLabel;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* MaxHealthLabel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CurrentHealth;
};
