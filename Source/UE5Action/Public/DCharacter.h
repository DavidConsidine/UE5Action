// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDInteractionComponent;
class UAnimMontage;

UCLASS()
class UE5ACTION_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void PrimaryInteract();
	void TryToJump();
	void PrimaryAttack_TimeElapsed();

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AActor> ProjectileClass;
	UPROPERTY(VisibleAnywhere)
	UDInteractionComponent* InteractionComp;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHandle_PrimaryAttack;
};
