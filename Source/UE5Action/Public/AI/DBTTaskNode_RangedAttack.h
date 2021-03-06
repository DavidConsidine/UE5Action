// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "DBTTaskNode_RangedAttack.generated.h"

/**
 * 
 */
UCLASS()
class UE5ACTION_API UDBTTaskNode_RangedAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

public:
	UDBTTaskNode_RangedAttack();

protected:

	UPROPERTY(EditAnywhere, Category="AI")
	float MaxProjectileSpread;

	UPROPERTY(EditAnywhere, Category="AI")
	TSubclassOf<AActor> ProjectileClass;
};
