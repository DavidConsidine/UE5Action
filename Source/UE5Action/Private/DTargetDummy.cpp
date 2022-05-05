// Fill out your copyright notice in the Description page of Project Settings.


#include "DTargetDummy.h"
#include "Components/StaticMeshComponent.h"
#include "DAttributeComponent.h"

// Sets default values
ADTargetDummy::ADTargetDummy()
{
    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    RootComponent = MeshComp;

    AttrComp = CreateDefaultSubobject<UDAttributeComponent>(TEXT("AttrComp"));
    // Trigger when health is changed (damage/healing)
    AttrComp->OnHealthChanged.AddDynamic(this, &ThisClass::OnHealthChanged);
}

void ADTargetDummy::OnHealthChanged(AActor* InstigatorActor, UDAttributeComponent* owningComp, float NewHealth, float Delta)
{
    if (Delta < 0.f)
    {
        MeshComp->SetScalarParameterValueOnMaterials("TimeToHit", GetWorld()->TimeSeconds);
    }
}
