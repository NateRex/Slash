// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.


#include "Components/AttributeComponent.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttributeComponent::ReceiveDamage(float Damage)
{
	Health = FMath::Clamp(Health - Damage, 0.f, MaxHealth);
}

void UAttributeComponent::UseStamina(float Cost)
{
	Stamina = FMath::Clamp(Stamina - Cost, 0.f, MaxStamina);
}

float UAttributeComponent::GetHealthPercent() const
{
	return Health / MaxHealth;
}

float UAttributeComponent::GetStaminaPercent() const
{
	return Stamina / MaxStamina;
}

bool UAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

void UAttributeComponent::AddGold(int32 Amt)
{
	Gold += Amt;
}

void UAttributeComponent::AddSouls(int32 Amt)
{
	Souls += Amt;
}

void UAttributeComponent::RegenStamina(float DeltaTime)
{
	Stamina = FMath::Clamp(Stamina + StaminaRegenRate * DeltaTime, 0.f, MaxStamina);
}
