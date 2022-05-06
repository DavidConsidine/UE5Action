// Fill out your copyright notice in the Description page of Project Settings.


#include "DProjectileDashAlt.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "particles/ParticleSystemComponent.h"

ADProjectileDashAlt::ADProjectileDashAlt()
{
	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MoveComp->InitialSpeed = 6000.f;
}

void ADProjectileDashAlt::Explode_Implementation()
{
	// Clear timer if Explode function call was already made through another source like OnActorHit
	GetWorldTimerManager().ClearTimer(TimerHandle_DelayedDetonate);
	if (ensure(ImpactFX))
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
	}
	FXComp->DeactivateSystem();

	MoveComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	// use local FTimerHandle as timer will never be stopped prematurely
	FTimerHandle TimerHandle_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHandle_DelayedTeleport, this, &ADProjectileDashAlt::TeleportInstigator, TeleportDelay);

	// skip base implementation as it will destroy actor (we need to stay alive a bit longer to finish the 2nd timer)
	//Super::Explode_Implementation();
}

void ADProjectileDashAlt::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation());
	}
}

void ADProjectileDashAlt::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_DelayedDetonate, this, &ADProjectileDashAlt::Explode, DetonateDelay);
}
