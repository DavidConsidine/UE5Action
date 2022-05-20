// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DAICharacter.generated.h"

class UPawnSensingComponent;
class UDAttributeComponent;

UCLASS()
class UE5ACTION_API ADAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADAICharacter();

protected:
	virtual void PostInitializeComponents() override;

	UFUNCTION()
	void OnPawnSeen(APawn* Pawn);

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UDAttributeComponent* owningComp, float NewHealth, float Delta);

	void SetTargetActor(AActor* NewTarget);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDAttributeComponent* AttrComp;
};
