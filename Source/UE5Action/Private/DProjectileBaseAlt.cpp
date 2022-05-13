// Fill out your copyright notice in the Description page of Project Settings.


#include "DProjectileBaseAlt.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundCue.h"
#include "Camera/CameraShakeBase.h"


ADProjectileBaseAlt::ADProjectileBaseAlt()
{
 	
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this, &ADProjectileBaseAlt::OnActorHit);
	RootComponent = SphereComp;

	FXComp = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FXComp"));
	FXComp->SetupAttachment(RootComponent);

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->SetupAttachment(RootComponent);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MoveComp"));
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
	MoveComp->InitialSpeed = 8000.f;

	ImpactShakeInnerRadius = 250.f;
	ImpactShakeOuterRadius = 2500.f;
}

void ADProjectileBaseAlt::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Explode();
}

// _Implementation from it being marked as BlueprintNativeEvent
void ADProjectileBaseAlt::Explode_Implementation()
{
	// check to make sure we aren't already being 'destroyed'
	// Adding ensure to see if we encounter this situation at all
	if (ensure(!IsPendingKill()) && ImpactFX != nullptr)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
		
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());

		UGameplayStatics::PlayWorldCameraShake(this, ImpactShake, GetActorLocation(), ImpactShakeInnerRadius, ImpactShakeOuterRadius);
		
		Destroy();
	}
}

void ADProjectileBaseAlt::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// SphereComp->ignoreActorWhenMoveing(GetInstigator(), true);
}

