// Fill out your copyright notice in the Description page of Project Settings.


#include "DMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADMagicProjectile::ADMagicProjectile()
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

void ADMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(TimerHandle_DestroyProjectile, this, &ThisClass::DestroyProjectile_TimeElapsed, MaxLifetime);
}

void ADMagicProjectile::DestroyProjectile_TimeElapsed()
{
	Destroy();
}
