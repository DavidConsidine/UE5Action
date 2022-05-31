// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeComponent.h"



UDAttributeComponent::UDAttributeComponent()
{
	HealthMax = 100.f;
	Health = HealthMax;
}

UDAttributeComponent* UDAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<UDAttributeComponent>(FromActor->GetComponentByClass(UDAttributeComponent::StaticClass()));
	}
	return nullptr;
}

bool UDAttributeComponent::IsActorAlive(AActor* Actor)
{
	UDAttributeComponent* AttrComp = GetAttributes(Actor);
	if (AttrComp)
	{
		return AttrComp->IsAlive();
	}
	return false;
}

bool UDAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged())
	{
		return false;
	}
	
	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.f, HealthMax);

	float ActualDelta = Health - OldHealth;

	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	return ActualDelta != 0;
}

bool UDAttributeComponent::IsAlive() const
{
	return Health > 0.f;
}

bool UDAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}

float UDAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool UDAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}

