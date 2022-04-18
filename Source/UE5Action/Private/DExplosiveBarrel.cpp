// Fill out your copyright notice in the Description page of Project Settings.


#include "DExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"


ADExplosiveBarrel::ADExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp;"));
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName("PhysicsActor");
	MeshComp->OnComponentHit.AddDynamic(this, &ThisClass::ComponentHit);

	ForceComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("ForceComp"));
	ForceComp->SetupAttachment(MeshComp);
	ForceComp->Radius = 600.f;
	ForceComp->ImpulseStrength = 2000.f;
	ForceComp->bImpulseVelChange = true;
	ForceComp->bAutoActivate = false;
}

void ADExplosiveBarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADExplosiveBarrel::ComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();
}



