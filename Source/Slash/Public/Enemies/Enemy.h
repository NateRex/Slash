// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Enemy.generated.h"

class AWeapon;
class UHealthBarComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class SLASH_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()

public:

	AEnemy();

	// AActor overrides
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	virtual void Destroyed() override;

	// IHitInterface overrides
	virtual void GetHit_Implementation(const FVector& ImpactPoint, const AActor* Hitter) override;

protected:

	// AActor overrides
	virtual void BeginPlay() override;

	// ABaseCharacter overrides
	virtual bool CanAttack() const override;
	virtual void Attack() override;
	virtual void AttackEnd() override;
	virtual void HandleDamage(float DamageAmount) override;
	virtual void Die() override;
	void SpawnSoul();

	UPROPERTY(BlueprintReadOnly)
	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

private:

	// AI Behavior
	void InitializeEnemy();
	AActor* ChoosePatrolTarget();
	void CheckPatrolTarget();
	void StartPatrolling();
	void ClearPatrolTimer();
	void PatrolTimerFinished();
	void CheckCombatTarget();
	void MoveToTarget(AActor* Target);
	void StartChasing();
	void LoseInterest();
	bool IsOutsideCombatRadius() const;
	bool IsChasing() const;
	bool InTargetRange(AActor* Target, double Radius) const;
	bool IsOutsideAttackRadius() const;
	bool IsInsideAttackRadius() const;
	bool IsAttacking() const;
	bool IsEngaged() const;
	void ClearAttackTimer();
	void StartAttackTimer();
	bool IsDead() const;
	void ShowHealthBar();
	void HideHealthBar();
	void SpawnDefaultWeapon();

	// callback for OnPawnSeen in PawnSensingComponent
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);
	
	AAIController* EnemyController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AWeapon> WeaponClass;

	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBar;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;

	FTimerHandle PatrolTimer;

	UPROPERTY(EditAnywhere)
	double PatrolRange = 200.f;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;

	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMin = 5.f;

	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float PatrolWaitMax = 10.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float PatrollingSpeed = 125.f;

	UPROPERTY(EditAnywhere)
	double CombatRange = 1000.f;

	FTimerHandle AttackTimer;

	UPROPERTY(EditAnywhere, Category = Combat)
	double AttackRange = 150.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	double MoveToTolerance = 50.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMin = 0.5f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float AttackMax = 1.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float ChasingSpeed = 300.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	float DeathLifeSpan = 8.f;

	UPROPERTY(EditAnywhere, Category = Combat)
	TSubclassOf<class ASoul> SoulClass;
};
