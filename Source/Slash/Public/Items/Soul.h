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

public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;
	virtual void OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:

	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	int32 SoulValue;

	UPROPERTY(EditAnywhere, Category = "Soul Properties")
	float DriftRate = 15.f;

	double DesiredZ;

public:

	FORCEINLINE int32 GetValue() const { return SoulValue; }
	FORCEINLINE void SetValue(int32 Amt) { SoulValue = Amt; }
};
