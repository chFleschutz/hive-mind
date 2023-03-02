// Copyright 2023 Christoph Fleschutz. All Rights Reserved.


#include "UI/HealthBar.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthBar::SetMaxHealth(const float NewMaxHealth)
{
	MaxHealth = NewMaxHealth;

	FNumberFormattingOptions Options;
	Options.SetMaximumFractionalDigits(0);
	MaxHealthLabel->SetText(FText::AsNumber(MaxHealth, &Options));

	UpdateHealthBar();
}

void UHealthBar::SetCurrentHealth(const float NewCurrentHealth)
{
	CurrentHealth = NewCurrentHealth;

	FNumberFormattingOptions Options;
	Options.SetMaximumFractionalDigits(0);
	CurrentHealthLabel->SetText(FText::AsNumber(CurrentHealth, &Options));

	UpdateHealthBar();
}

void UHealthBar::UpdateHealthBar() const
{
	HealthBar->SetPercent(CurrentHealth / MaxHealth);
}
