// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Soul.generated.h"

class UNiagaraSystem;

UCLASS()
class SLASH_API ASoul : public AItem
{
	GENERATED_BODY()

protected:

	virtual void OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 SoulValue;

public:

	FORCEINLINE int32 GetValue() const { return SoulValue; }
	FORCEINLINE void SetValue(int32 Amt) { SoulValue = Amt; }
};
