// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGameplayInterface.h"
#include "DPowerUpActor.generated.h"

class USphereComponent;

UCLASS()
class UE5ACTION_API ADPowerUpActor : public AActor, public IDGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ADPowerUpActor();

	void Interact_Implementation(APawn* InstigatorPawn) override;

protected:
	UFUNCTION()
	void ShowPowerUp();

	void HideAndCooldownPowerUp();

	void SetPowerUpState(bool bNewIsActive);

protected:
	UPROPERTY(EditAnywhere, Category="PowerUp")
	float RespawnTime;

	FTimerHandle TimerHandle_RespawnTime;

	UPROPERTY(VisibleAnywhere, Category="Components")
	USphereComponent* SphereComp;
};
