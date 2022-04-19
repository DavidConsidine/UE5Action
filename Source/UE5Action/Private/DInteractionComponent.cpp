// Fill out your copyright notice in the Description page of Project Settings.


#include "DInteractionComponent.h"
#include "DGameplayInterface.h"
#include "DrawDebugHelpers.h"

UDInteractionComponent::UDInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	TraceDistance = 1000.f;
}

void UDInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UDInteractionComponent::PrimaryInteract()
{
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

	FVector EyeLocation;
	FRotator EyeRotation;
	GetOwner()->GetActorEyesViewPoint(EyeLocation, EyeRotation);
	FVector End = EyeLocation + (EyeRotation.Vector() * TraceDistance);

	float Radius = 30.f;

	//FHitResult Hit;
	//bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, EyeLocation, End, ObjectQueryParams);
	TArray<FHitResult> Hits;
	FCollisionShape CollisionShape;
	CollisionShape.SetSphere(Radius);
	bool bBlockingHit = GetWorld()->SweepMultiByObjectType(Hits, EyeLocation, End, FQuat::Identity, ObjectQueryParams, CollisionShape);
	FColor LineColor = bBlockingHit ? FColor::Green : FColor::Red;

	for (auto Hit : Hits)
	{
		//FVector DebugEndLocation = bBlockingHit ? Hit.ImpactPoint : End;
		DrawDebugSphere(GetWorld(), Hit.ImpactPoint, Radius, 32, LineColor, false, 2.f);
		AActor* HitActor = Hit.GetActor();
		if (HitActor)
		{
			if (HitActor->Implements<UDGameplayInterface>())
			{
				APawn* Owner = Cast<APawn>(GetOwner());
				IDGameplayInterface::Execute_Interact(HitActor, Owner);
				break;
			}
		}
	}
	DrawDebugLine(GetWorld(), EyeLocation, End, LineColor, false, 2.f, 0, 2.f);
}

void UDInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}
