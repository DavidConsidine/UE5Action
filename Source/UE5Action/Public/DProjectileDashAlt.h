// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DProjectileBaseAlt.h"
#include "DProjectileDashAlt.generated.h"

/**
 * 
 */
UCLASS()
class UE5ACTION_API ADProjectileDashAlt : public ADProjectileBaseAlt
{
	GENERATED_BODY()
public:
	ADProjectileDashAlt();

protected:
	UPROPERTY(EditDefaultsOnly, Category="Teleport")
	float TeleportDelay;

	UPROPERTY(EditDefaultsOnly, Category = "Teleport")
	float DetonateDelay;

	// Handle to cancel timer if we already hit something
	FTimerHandle TimerHandle_DelayedDetonate;

protected:
	// Base class using BlueprintNativeEvent, we must override the _Implementation not the Explode()
	virtual void Explode_Implementation() override;

	void TeleportInstigator();
	
	virtual void BeginPlay() override;
};
