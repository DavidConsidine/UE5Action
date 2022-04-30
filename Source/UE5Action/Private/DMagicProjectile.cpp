// Fill out your copyright notice in the Description page of Project Settings.


#include "DMagicProjectile.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleSystem.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DAttributeComponent.h"

ADMagicProjectile::ADMagicProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ADMagicProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	//SphereComp->OnComponentHit.AddDynamic(this, &ThisClass::OnActorHit);
}

void ADMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ADMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OtherActorAsPawn = Cast<APawn>(OtherActor);
	if (OtherActorAsPawn != nullptr && OtherActorAsPawn == GetInstigator())
	{
		return;
	}
	
	if (OtherActor)
	{
		UDAttributeComponent* AttrComp = Cast<UDAttributeComponent>(OtherActor->GetComponentByClass(UDAttributeComponent::StaticClass()));
		if (AttrComp)
		{
			AttrComp->ApplyHealthChange(-20.f);
		}
	
		if (ImpactParticleSystem != nullptr)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactParticleSystem, GetActorTransform());
		}
		// Stop DestroyProjectile timer if it is set and has not fired.
		GetWorldTimerManager().ClearTimer(TimerHandle_DestroyProjectile);
		DestroyProjectile_TimeElapsed();
	}
}

void ADMagicProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	
}
