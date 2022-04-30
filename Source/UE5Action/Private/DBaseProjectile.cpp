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
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnActorHit);
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
	//SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	GetWorldTimerManager().SetTimer(TimerHandle_DestroyProjectile, this, &ThisClass::DestroyProjectile_TimeElapsed, MaxLifetime);
}

void ADBaseProjectile::DestroyProjectile_TimeElapsed()
{
	Destroy();
}

void ADBaseProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// For now, leave this empty and override in child classes for class-specific behaviours.
}

void ADBaseProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Override with class specific behaviour in child classes
}

void ADBaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

