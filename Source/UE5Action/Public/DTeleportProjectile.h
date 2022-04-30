// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBaseProjectile.h"
#include "DTeleportProjectile.generated.h"

class UParticleSystem;

UCLASS()
class UE5ACTION_API ADTeleportProjectile : public ADBaseProjectile
{
	GENERATED_BODY()
public:
	ADTeleportProjectile();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

protected:
	virtual void DestroyProjectile_TimeElapsed() override;
	void TeleportInstigator_TimeElapsed();
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* ExplosionParticleSystem;

	FTimerHandle TimerHandle_TeleportInstigator;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float WaitTimeToTeleport;
};
