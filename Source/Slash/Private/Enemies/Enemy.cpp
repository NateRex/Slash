// Copyright (c) 2024 Nathaniel Rex. No Rights Reserved.


#include "Enemies/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/AttributeComponent.h"
#include "HUD/HealthBarComponent.h"

AEnemy::AEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);

	USkeletalMeshComponent* SkeletalMesh = GetMesh();
	SkeletalMesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	SkeletalMesh->SetGenerateOverlapEvents(true);

	Attributes = CreateDefaultSubobject<UAttributeComponent>(TEXT("Attributes"));

	HealthBar = CreateDefaultSubobject<UHealthBarComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(GetRootComponent());
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::PlayHitReactMontage(const FName& SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && HitReactMontage)
	{
		AnimInstance->Montage_Play(HitReactMontage);
		AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
	}
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::GetHit_Implementation(const FVector& ImpactPoint)
{
	DirectionalHitReact(ImpactPoint);

	if (HitSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			HitSound,
			ImpactPoint);
	}

	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			HitParticles,
			ImpactPoint);
	}
}

void AEnemy::DirectionalHitReact(const FVector& ImpactPoint)
{
	const FVector Forward = GetActorForwardVector();
	const FVector ActorLocation = GetActorLocation();
	const FVector ImpactAdjusted(ImpactPoint.X, ImpactPoint.Y, ActorLocation.Z);
	const FVector ToHit = (ImpactAdjusted - GetActorLocation()).GetSafeNormal();
	const double Dot = FVector::DotProduct(Forward, ToHit);
	double Angle = FMath::RadiansToDegrees(FMath::Acos(Dot));

	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Angle *= -1.f;
	}

	FName Section("FromBack");
	if (Angle >= -45.f && Angle < 45.f)
	{
		Section = FName("FromFront");
	}
	else if (Angle >= -135.f && Angle < -45.f)
	{
		Section = FName("FromLeft");
	}
	else if (Angle >= 45.f && Angle < 135.f)
	{
		Section = FName("FromRight");
	}
	PlayHitReactMontage(Section);
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (Attributes)
	{
		Attributes->ReceiveDamage(DamageAmount);

		if (HealthBar)
		{
			HealthBar->SetHealthPercent(Attributes->GetHealthPercent());
		}
	}

	return DamageAmount;
}

