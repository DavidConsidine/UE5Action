// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DExplosiveBarrel.generated.h"

class UStaticMeshComponent;
class URadialForceComponent;
class UPrimitiveComponent;

UCLASS()
class UE5ACTION_API ADExplosiveBarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	ADExplosiveBarrel();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComp;
	UPROPERTY(EditAnywhere)
	URadialForceComponent* ForceComp;
};
