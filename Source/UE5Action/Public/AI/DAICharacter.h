// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DAICharacter.generated.h"

class UPawnSensingComponent;

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

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;
};
