// Fill out your copyright notice in the Description page of Project Settings.


#include "DBlackholeProjectile.h"
#include "Components/SphereComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"

ADBlackholeProjectile::ADBlackholeProjectile()
{
	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(RootComponent);
	ForceComp->bIgnoreOwningActor = true;
	ForceComp->AddCollisionChannelToAffect(ECollisionChannel::ECC_WorldDynamic);
	ForceComp->AddCollisionChannelToAffect(ECollisionChannel::ECC_WorldStatic);
	ForceComp->AddCollisionChannelToAffect(ECollisionChannel::ECC_PhysicsBody);

	ForceComp->Radius = 500.f;
	ForceComp->ForceStrength = -2000.f;
}

void ADBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SphereComp->SetCollisionProfileName("BlackholeProjectile");
	//SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ADBlackholeProjectile::OnActorOverlap);
}

void ADBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADBlackholeProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APawn* OtherActorAsPawn = Cast<APawn>(OtherActor);
	if (OtherActorAsPawn != nullptr && OtherActorAsPawn == GetInstigator())
	{
		return;
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("Overlap Actor: %s, Physics?: %d"), *OtherActor->GetName(), OverlappedComponent->IsSimulatingPhysics()));
	OtherActor->Destroy();
}
