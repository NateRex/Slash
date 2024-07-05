// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.


#include "HUD/HealthBarComponent.h"
#include "HUD/HealthBarWidget.h"
#include "Components/ProgressBar.h"

void UHealthBarComponent::SetHealthPercent(float Percent)
{
	if (HealthWidget == nullptr)
	{
		HealthWidget = Cast<UHealthBarWidget>(GetUserWidgetObject());
	}
	
	if (HealthWidget && HealthWidget->HealthBar)
	{
		HealthWidget->HealthBar->SetPercent(Percent);
	}
}
