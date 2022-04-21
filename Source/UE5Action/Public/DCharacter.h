// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDInteractionComponent;
class UAnimMontage;
class UUserWidget;
class ADBaseProjectile;

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
	void SecondaryAttack();
	void PrimaryInteract();
	void TryToJump();
	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack_TimeElapsed();

private:
	void LaunchProjectile(TSubclassOf<AActor>& Projectile, FHitResult& Hit);

protected:
	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComp;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AActor> PrimaryProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AActor> SecondaryProjectileClass;
	UPROPERTY(VisibleAnywhere)
	UDInteractionComponent* InteractionComp;
	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float ProjectileTrace;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondaryAttack;
};
