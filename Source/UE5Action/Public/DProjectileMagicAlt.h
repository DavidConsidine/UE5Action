// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DProjectileBaseAlt.h"
#include "DProjectileMagicAlt.generated.h"

/**
 * 
 */
UCLASS()
class UE5ACTION_API ADProjectileMagicAlt : public ADProjectileBaseAlt
{
	GENERATED_BODY()
public:
	ADProjectileMagicAlt();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) override;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float DamageAmount;
};
