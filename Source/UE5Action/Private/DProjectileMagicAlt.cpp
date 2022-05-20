// Fill out your copyright notice in the Description page of Project Settings.


#include "DProjectileMagicAlt.h"
#include "DAttributeComponent.h"
#include "Components/SphereComponent.h"

ADProjectileMagicAlt::ADProjectileMagicAlt()
{
	DamageAmount = 20.f;
}

void ADProjectileMagicAlt::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->IgnoreActorWhenMoving(GetInstigator(), true);
	SphereComp->OnComponentHit.AddDynamic(this, &ADProjectileMagicAlt::OnActorHit);
	SphereComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
}

void ADProjectileMagicAlt::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::OnActorHit(HitComponent, OtherActor, OtherComp, NormalImpulse, Hit);

	UDAttributeComponent* AttrComp = Cast<UDAttributeComponent>(OtherActor->GetComponentByClass(UDAttributeComponent::StaticClass()));
	if (AttrComp)
	{
		AttrComp->ApplyHealthChange(GetInstigator(), -DamageAmount);
	}
}
