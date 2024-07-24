// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupInterface.generated.h"

class AItem;
class ASoul;
class ATreasure;

UINTERFACE(MinimalAPI)
class UPickupInterface : public UInterface
{
	GENERATED_BODY()
};

class SLASH_API IPickupInterface
{
	GENERATED_BODY()

public:

	virtual void SetOverlappingItem(AItem* Item) = 0;
	virtual void AddSouls(ASoul* Soul) = 0;
	virtual void AddGold(ATreasure* Treasure) = 0;
};
