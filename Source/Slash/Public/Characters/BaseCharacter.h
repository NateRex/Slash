// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "BaseCharacter.generated.h"

class AWeapon;
class UAttributeComponent;
class UAnimMontage;

UCLASS()
class SLASH_API ABaseCharacter : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:
	ABaseCharacter();

	/** AActor overrides */
	virtual void Tick(float DeltaTime) override;

protected:

	/** AActor overrides */
	virtual void BeginPlay() override;

	/** IHitInterface overrides */
	virtual void GetHit_Implementation(const FVector& ImpactPoint, const AActor* Hitter) override;

	/** Combat */
	virtual bool CanAttack() const;
	virtual void Attack();
	void DirectionalHitReact(const FVector& ImpactPoint);
	virtual void HandleDamage(float DamageAmount);
	bool IsAlive() const;

	UFUNCTION(BlueprintNativeEvent)
	void Die();

	void PlayHitSound(const FVector& ImpactPoint);
	void SpawnHitParticles(const FVector& ImpactPoint);
	void DisableCapsule();
	void EnableMeshCollision();
	void DisableMeshCollision();

	/** Montage */
	virtual int32 PlayAttackMontage();
	virtual void PlayDodgeMontage();
	void PlayHitReactMontage(const FName& SectionName);
	virtual int32 PlayDeathMontage();
	void StopAttackMontage();

	UFUNCTION(BlueprintCallable)
	FVector GetTranslationWarpTarget();
	
	UFUNCTION(BlueprintCallable)
	FVector GetRotationWarpTarget();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	UFUNCTION(BlueprintCallable)
	virtual void DodgeEnd();

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);
	
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleInstanceOnly, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(BlueprintReadOnly, Category = Combat)
	APawn* CombatTarget;

	UPROPERTY(EditAnywhere, Category = Combat)
	double WarpTargetDistance = 90.f;

	UPROPERTY(BlueprintReadOnly)
	TEnumAsByte<EDeathPose> DeathPose;

private:

	/** Combat */
	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);
	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);

	UPROPERTY(EditAnywhere, Category = Combat)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = Combat)
	UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSections;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;

public:

	FORCEINLINE TEnumAsByte<EDeathPose> GetDeathPose() const { return DeathPose; }
};