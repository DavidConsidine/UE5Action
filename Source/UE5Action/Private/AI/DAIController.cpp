// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/Blackboardcomponent.h"

void ADAIController::BeginPlay()
{
	Super::BeginPlay();
	if (ensureMsgf(BehaviorTree, TEXT("Behavior Tree is nullptr! Please assign BehaviorTree in your AI Controller.")))
	{
		RunBehaviorTree(BehaviorTree);
	}


	/*APawn* MyPawn = UGameplayStatics::GetPlayerPawn(this, 0);
	
	if (MyPawn)
	{
		GetBlackboardComponent()->SetValueAsVector("MoveToLocation", MyPawn->GetActorLocation());
		GetBlackboardComponent()->SetValueAsObject("TargetActor", MyPawn);
	}*/
}
