// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DBaseProjectile.h"
#include "DBlackholeProjectile.generated.h"

class URadialForceComponent;

UCLASS()
class UE5ACTION_API ADBlackholeProjectile : public ADBaseProjectile
{
	GENERATED_BODY()
public:
	ADBlackholeProjectile();
	virtual void PostInitializeComponents() override;
	virtual void Tick(float DeltaTime) override;

protected:
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
protected:
	UPROPERTY(VisibleAnywhere)
	URadialForceComponent* ForceComp;
};
