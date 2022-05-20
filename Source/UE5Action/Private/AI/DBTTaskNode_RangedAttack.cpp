// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DBTTaskNode_RangedAttack.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DAttributeComponent.h"

UDBTTaskNode_RangedAttack::UDBTTaskNode_RangedAttack()
{
	MaxProjectileSpread = 2.f;
}

EBTNodeResult::Type UDBTTaskNode_RangedAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* MyController = OwnerComp.GetAIOwner();
	if(ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_Front");

		AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TargetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		if (!UDAttributeComponent::IsActorAlive(TargetActor))
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TargetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		MuzzleRotation.Pitch += FMath::RandRange(0.f, MaxProjectileSpread);
		MuzzleRotation.Yaw += FMath::RandRange(-MaxProjectileSpread, MaxProjectileSpread);

		FActorSpawnParameters SpawnParams;
		SpawnParams.Instigator = MyPawn;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);

		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}
