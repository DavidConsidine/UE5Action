// Fill out your copyright notice in the Description page of Project Settings.


#include "DMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

ADMagicProjectile::ADMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}
