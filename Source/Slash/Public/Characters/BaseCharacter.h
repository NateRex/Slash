#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
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

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled);

protected:

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* Attributes;

	UPROPERTY(VisibleInstanceOnly, Category = Weapon)
	AWeapon* EquippedWeapon;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> AttackMontageSections;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, Category = Combat)
	TArray<FName> DeathMontageSections;

	virtual void BeginPlay() override;

	virtual bool CanAttack() const;

	virtual void Attack();

	UFUNCTION(BlueprintCallable)
	virtual void AttackEnd();

	void DirectionalHitReact(const FVector& ImpactPoint);

	virtual void Die();

	bool IsAlive() const;

	void PlayHitSound(const FVector& ImpactPoint);

	void SpawnHitParticles(const FVector& ImpactPoint);

	virtual void HandleDamage(float DamageAmount);

	void PlayMontageSection(UAnimMontage* Montage, const FName& SectionName);

	int32 PlayRandomMontageSection(UAnimMontage* Montage, const TArray<FName>& SectionNames);

	virtual int32 PlayAttackMontage();

	void PlayHitReactMontage(const FName& SectionName);

	virtual int32 PlayDeathMontage();

	void DisableCapsule();

private:

	UPROPERTY(EditAnywhere, Category = Sounds)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category = "Visual Effects")
	UParticleSystem* HitParticles;
};