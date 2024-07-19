// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.


#include "HUD/SlashOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USlashOverlay::SetHealthBarPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetStaminaBarPercent(float Percent)
{
	if (StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetCoinText(int32 Coins)
{
	if (CoinText)
	{
		FString String = FString::Printf(TEXT("%d"), Coins);
		CoinText->SetText(FText::FromString(String));
	}
}

void USlashOverlay::SetSoulText(int32 Souls)
{
	if (SoulText)
	{
		FString String = FString::Printf(TEXT("%d"), Souls);
		SoulText->SetText(FText::FromString(String));
	}
}
