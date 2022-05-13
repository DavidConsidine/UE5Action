// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DProjectileBaseAlt.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UAudioComponent;
class USoundCue;
class UCameraShakeBase;

// 'ABSTRACT' marks this class as incomplete,
// keeping this out of certain dropdown windows like SpawnActor in Unreal Editor
UCLASS(ABSTRACT) 
class UE5ACTION_API ADProjectileBaseAlt : public AActor
{
	GENERATED_BODY()
	
public:
	ADProjectileBaseAlt();

protected:
	UPROPERTY(EditDefaultsOnly, Category="FX|Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	UPROPERTY(EditDefaultsOnly, Category = "FX|Shake")
	float ImpactShakeInnerRadius;

	UPROPERTY(EditDefaultsOnly, Category = "FX|Shake")
	float ImpactShakeOuterRadius;

	UPROPERTY(EditDefaultsOnly, Category="FX")
	UParticleSystem* ImpactFX;

	UPROPERTY(EditDefaultsOnly, Category = "FX")
	USoundCue* ImpactSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UProjectileMovementComponent* MoveComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UParticleSystemComponent* FXComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UAudioComponent* AudioComp;

protected:
	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// BlueprintNativeEvent = C++ base implementation, can be extended in Blueprints
	// BlueprintCallable to allow child (Blueprint) classes to trigger explosions
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;
};
