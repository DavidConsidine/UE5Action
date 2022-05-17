// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/DAICharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"
#include "DAttributeComponent.h"
#include "BrainComponent.h"

ADAICharacter::ADAICharacter()
{
    PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComp"));

    AttrComp = CreateDefaultSubobject<UDAttributeComponent>(TEXT("AttrComp"));

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void ADAICharacter::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    PawnSensingComp->OnSeePawn.AddDynamic(this, &ADAICharacter::OnPawnSeen);

    AttrComp->OnHealthChanged.AddDynamic(this, &ADAICharacter::OnHealthChanged);
}

void ADAICharacter::OnPawnSeen(APawn* Pawn)
{
    AAIController* AIC = Cast<AAIController>(GetController());
    if (AIC)
    {
        UBlackboardComponent* BBComp = AIC->GetBlackboardComponent();
        BBComp->SetValueAsObject("TargetActor", Pawn);

        DrawDebugString(GetWorld(), GetActorLocation(), "PLAYER SPOTTED", nullptr, FColor::White, 4.f, true);
    }
}

void ADAICharacter::OnHealthChanged(AActor* InstigatorActor, UDAttributeComponent* owningComp, float NewHealth, float Delta)
{
    if (Delta < 0.f)
    {
        if (NewHealth <= 0.f)
        {
            AAIController* AIC = Cast<AAIController>(GetController());
            if (AIC != nullptr)
            {
                AIC->GetBrainComponent()->StopLogic("Killed");
            }

            GetMesh()->SetAllBodiesSimulatePhysics(true);
            GetMesh()->SetCollisionProfileName("Ragdoll");

            SetLifeSpan(10.f);
        }
    }

    if (NewHealth <= 0.f && Delta < 0.f)
    {
        AAIController* AIC = Cast<AAIController>(GetController());
        if (AIC != nullptr)
        {
            //DisableInput(PC);
        }
    }
}
