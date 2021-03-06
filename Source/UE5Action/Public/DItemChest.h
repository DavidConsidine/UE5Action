// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DGameplayInterface.h"
#include "DItemChest.generated.h"

class UStaticMeshComponent;

UCLASS()
class UE5ACTION_API ADItemChest : public AActor, public IDGameplayInterface
{
	GENERATED_BODY()
	
public:	
	ADItemChest();

	void Interact_Implementation(APawn* InstigatorPawn);

	UPROPERTY(EditAnywhere)
	float TargetPitch;

protected:

protected:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* BaseMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* LidMesh;
};
