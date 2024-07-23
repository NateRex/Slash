// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.


#include "Items/Treasure.h"
#include "Characters/SlashCharacter.h"

void ATreasure::OnSphereStartOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ASlashCharacter* SlashCharacter = Cast<ASlashCharacter>(OtherActor);
	if (SlashCharacter)
	{
		SpawnPickupSound();
		Destroy();
	}
}
