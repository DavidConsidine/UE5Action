// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DBaseProjectile.h"
#include "DMagicProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;

UCLASS()
class UE5ACTION_API ADMagicProjectile : public ADBaseProjectile
{
	GENERATED_BODY()
	
public:
	ADMagicProjectile();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* ImpactParticleSystem;
};
