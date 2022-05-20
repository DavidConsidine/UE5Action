// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeComponent.h"

UDAttributeComponent::UDAttributeComponent()
{
	HealthMax = 100.f;
	Health = HealthMax;
}


bool UDAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
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

