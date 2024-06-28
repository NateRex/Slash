// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	

	AItem();
	virtual void Tick(float DeltaTime) override;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude = 0.25f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant = 5.f;

	UFUNCTION(BlueprintPure)
	float TransformedSin() const;

	UFUNCTION(BlueprintPure)
	float TransformedCos() const;

	template<typename T>
	T Avg(T First, T Second) const;

	virtual void BeginPlay() override;
	

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;

};


template<typename T>
inline T AItem::Avg(T First, T Second) const
{
	return (First + Second) / 2;
}