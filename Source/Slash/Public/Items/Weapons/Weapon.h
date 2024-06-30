// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

UCLASS()
class SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()
	

public:

	void Equip(USceneComponent* InParent, FName InSocketName);

	void AttachMeshToSocket(USceneComponent* InParent, const FName& InSocketName);
};
