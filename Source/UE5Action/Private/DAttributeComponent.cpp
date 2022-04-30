// Fill out your copyright notice in the Description page of Project Settings.


#include "DAttributeComponent.h"

UDAttributeComponent::UDAttributeComponent()
{
	Health = 100.f;
}


bool UDAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;

	return true;
}

