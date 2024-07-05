// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBarWidget.generated.h"

class UProgressBar;

UCLASS()
class SLASH_API UHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	// Field name in CPP must match name inside blueprint
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
};
