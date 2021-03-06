// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UDInteractionComponent;
class UDAttributeComponent;
class UAnimMontage;
class UUserWidget;
class ADBaseProjectile;
class UParticleSystem;

UCLASS()
class UE5ACTION_API ADCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Exec)
	void HealSelf(float Amount = 100);

protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void PrimaryAttack();
	void SecondaryAttack();
	void StartAttackEffects();
	void Teleport();
	void PrimaryInteract();
	void TryToJump();
	void PrimaryAttack_TimeElapsed();
	void SecondaryAttack_TimeElapsed();
	void Teleport_TimeElapsed();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, UDAttributeComponent* owningComp, float NewHealth, float Delta);

private:
	void LaunchProjectile(TSubclassOf<AActor>& Projectile);

protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UCameraComponent* CameraComp;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AActor> PrimaryProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<class AActor> SecondaryProjectileClass;
	UPROPERTY(EditAnywhere, Category = "Abilities")
	TSubclassOf<class AActor> TeleportProjectileClass;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UDInteractionComponent* InteractionComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UDAttributeComponent* AttrComp;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UAnimMontage* AttackAnim;
	UPROPERTY(EditAnywhere, Category = "Attack")
	float ProjectileTrace;

	UPROPERTY(VisibleAnywhere, Category="Effects")
	FName HandSocketName;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	UPROPERTY(EditAnywhere, Category = "Attack")
	UParticleSystem* CastingEffect;

	FTimerHandle TimerHandle_PrimaryAttack;
	FTimerHandle TimerHandle_SecondaryAttack;
	FTimerHandle TimerHandle_Teleport;
};
