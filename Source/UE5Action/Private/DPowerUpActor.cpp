// Fill out your copyright notice in the Description page of Project Settings.


#include "DPowerUpActor.h"
#include "Components/SphereComponent.h"

ADPowerUpActor::ADPowerUpActor()
{
    SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
    SphereComp->SetCollisionProfileName("PowerUp");
    RootComponent = SphereComp;

    RespawnTime = 10.f;
}

void ADPowerUpActor::Interact_Implementation(APawn* InstigatorPawn)
{
    // logic in derived classes..
}

void ADPowerUpActor::ShowPowerUp()
{
    SetPowerUpState(true);
}

void ADPowerUpActor::HideAndCooldownPowerUp()
{
    SetPowerUpState(false);

    GetWorldTimerManager().SetTimer(TimerHandle_RespawnTime, this, &ADPowerUpActor::ShowPowerUp, RespawnTime);
}

void ADPowerUpActor::SetPowerUpState(bool bNewIsActive)
{
    SetActorEnableCollision(bNewIsActive);

    //Set visibility on root and all childern
    RootComponent->SetVisibility(bNewIsActive, true);
}


