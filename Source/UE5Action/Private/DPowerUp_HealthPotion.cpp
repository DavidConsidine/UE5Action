// Fill out your copyright notice in the Description page of Project Settings.


#include "DPowerUp_HealthPotion.h"
#include "Components/StaticMeshComponent.h"
#include "DAttributeComponent.h"

ADPowerUp_HealthPotion::ADPowerUp_HealthPotion()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	// Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ADPowerUp_HealthPotion::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	UDAttributeComponent* AttrComp = Cast<UDAttributeComponent>(InstigatorPawn->GetComponentByClass(UDAttributeComponent::StaticClass()));
	// check if not already at max health
	if (ensure(AttrComp) && !AttrComp->IsFullHealth())
	{
		// Only activate if healed successfully
		if (AttrComp->ApplyHealthChange(AttrComp->GetHealthMax()))
		{
			HideAndCooldownPowerUp();
		}
	}
}
