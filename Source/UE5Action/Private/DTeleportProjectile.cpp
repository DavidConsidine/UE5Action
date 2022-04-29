// Fill out your copyright notice in the Description page of Project Settings.


#include "DTeleportProjectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Pawn.h"

ADTeleportProjectile::ADTeleportProjectile()
{
	MaxLifetime = 0.2;
	WaitTimeToTeleport = 0.2f;
}

void ADTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
}

void ADTeleportProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
}

void ADTeleportProjectile::DestroyProjectile_TimeElapsed()
{
	// Stop projectile particles from displaying
	EffectComp->SetActive(false);
	EffectComp->SetHiddenInGame(true);
	//Stop projectile moving any further
	MovementComp->StopMovementImmediately();
	// Turn off collision to prevent any unexpected behaviour
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Play 'detonation' particle system
	if (ExplosionParticleSystem)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticleSystem, GetActorTransform());
	}

	// Set Timer for Instigator teleport
	GetWorldTimerManager().SetTimer(TimerHandle_TeleportInstigator, this, &ThisClass::TeleportInstigator_TimeElapsed, WaitTimeToTeleport);
}

void ADTeleportProjectile::TeleportInstigator_TimeElapsed()
{
	APawn* InstigatorPawn = GetInstigator();
	InstigatorPawn->TeleportTo(GetActorLocation(), InstigatorPawn->GetActorRotation());
	Destroy();
}

void ADTeleportProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	APawn* HitPawn = Cast<APawn>(OtherActor);
	if (HitPawn != nullptr && HitPawn == GetInstigator())
	{
		return;
	}
	// Stop DestroyProjectile timer if it is set and has not fired.
	GetWorldTimerManager().ClearTimer(TimerHandle_DestroyProjectile);
	DestroyProjectile_TimeElapsed();
}
