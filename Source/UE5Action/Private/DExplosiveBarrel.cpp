// Fill out your copyright notice in the Description page of Project Settings.


#include "DExplosiveBarrel.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "DrawDebugHelpers.h"


ADExplosiveBarrel::ADExplosiveBarrel()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp;"));
	RootComponent = MeshComp;
	MeshComp->SetSimulatePhysics(true);
	MeshComp->SetCollisionProfileName("PhysicsActor");

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

void ADExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	MeshComp->OnComponentHit.AddDynamic(this, &ThisClass::ComponentHit);
}

void ADExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}



void ADExplosiveBarrel::ComponentHit_Implementation(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComp->FireImpulse();

	UE_LOG(LogTemp, Log, TEXT("OnComponentHit in Explosive Barrel"));

	// %s = string
	// %f = float
	// logs: "OtherActor: MyActor_1, at game time: 124.4"
	UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s, at game time: %f"), *GetNameSafe(OtherActor), GetWorld()->TimeSeconds);

	FString CombinedString = FString::Printf(TEXT("Hit at location: %s"), *Hit.ImpactPoint.ToString());
	DrawDebugString(GetWorld(), Hit.ImpactPoint, CombinedString, nullptr, FColor::Green, 2.f, true);
}



