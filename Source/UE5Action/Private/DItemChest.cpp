// Fill out your copyright notice in the Description page of Project Settings.


#include "DItemChest.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ADItemChest::ADItemChest()
{
	PrimaryActorTick.bCanEverTick = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	RootComponent = BaseMesh;

	LidMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LidMesh"));
	LidMesh->SetupAttachment(BaseMesh);

	TargetPitch = 110.f;
}

void ADItemChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADItemChest::Interact_Implementation(APawn* InstigatorPawn)
{
	LidMesh->SetRelativeRotation(FRotator(TargetPitch, 0.f, 0.f));
}

void ADItemChest::BeginPlay()
{
	Super::BeginPlay();
	
}
