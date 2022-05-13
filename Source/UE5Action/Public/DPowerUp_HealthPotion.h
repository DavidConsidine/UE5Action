// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DPowerUpActor.h"
#include "DPowerUp_HealthPotion.generated.h"

class UStaticMeshComponent;

UCLASS()
class UE5ACTION_API ADPowerUp_HealthPotion : public ADPowerUpActor
{
	GENERATED_BODY()
public:
	ADPowerUp_HealthPotion();

protected:
	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UStaticMeshComponent* MeshComp;
};
