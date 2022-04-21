// Fill out your copyright notice in the Description page of Project Settings.


#include "DBaseProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADBaseProjectile::ADBaseProjectile()
{
 	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("Projectile");
	RootComponent = SphereComp;

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EffectComp"));
	EffectComp->SetupAttachment(SphereComp);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovementComp"));
	MovementComp->InitialSpeed = 1000.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;

	MaxLifetime = 5.f;
}

void ADBaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DestroyProjectile, this, &ThisClass::DestroyProjectile_TimeElapsed, MaxLifetime);
}

void ADBaseProjectile::DestroyProjectile_TimeElapsed()
{
	Destroy();
}

void ADBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

