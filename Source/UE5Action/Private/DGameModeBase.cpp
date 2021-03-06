// Fill out your copyright notice in the Description page of Project Settings.


#include "DGameModeBase.h"
#include "EnvironmentQuery/EnvQueryManager.h"
#include "EnvironmentQuery/EnvQueryInstanceBlueprintWrapper.h"
#include "AI/DAICharacter.h"
#include "DAttributeComponent.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"

ADGameModeBase::ADGameModeBase()
{
	SpawnTimerInterval = 2.f;
}

void ADGameModeBase::StartPlay()
{
	Super::StartPlay();

	// Continuous timer to spawn in more bots.
	// Actual amount of bots and whether its allowed to spawn logic later in the chain...
	GetWorldTimerManager().SetTimer(TimerHandle_SpawnBots, this, &ADGameModeBase::SpawnBotTimerElapsed, SpawnTimerInterval, true);
}

void ADGameModeBase::KillAll()
{
	for (TActorIterator<ADAICharacter> It(GetWorld()); It; ++It)
	{
		ADAICharacter* Bot = *It;

		UDAttributeComponent* AttrComp = UDAttributeComponent::GetAttributes(Bot);
		if (ensure(AttrComp) && AttrComp->IsAlive())
		{
			AttrComp->Kill(this);	// @fixme: pass in player? for kill credit
		}
	}
}

void ADGameModeBase::SpawnBotTimerElapsed()
{
	int32 NrOfAliveBots = 0;
	for (TActorIterator<ADAICharacter> It(GetWorld()); It; ++It)
	{
		ADAICharacter* Bot = *It;

		UDAttributeComponent* AttrComp = UDAttributeComponent::GetAttributes(Bot);
		if (ensure(AttrComp) && AttrComp->IsAlive())
		{
			NrOfAliveBots++;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Found %i alive bots."), NrOfAliveBots);

	float MaxBotCount = 10.f;
	if (DifficultyCurve)
	{
		MaxBotCount = DifficultyCurve->GetFloatValue(GetWorld()->TimeSeconds);
	}

	if (NrOfAliveBots >= MaxBotCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("At maximum bot capacity. Skipping bot spawn"));
		return;
	}

	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnBotQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if (ensure(QueryInstance))
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ADGameModeBase::OnQueryCompleted);
	}
}

void ADGameModeBase::OnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if (QueryStatus != EEnvQueryStatus::Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn bot EQS Query Failed!"));

		return;
	}

	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();

	if (Locations.IsValidIndex(0))
	{
		GetWorld()->SpawnActor<AActor>(MinionClass, Locations[0], FRotator::ZeroRotator);

		DrawDebugSphere(GetWorld(), Locations[0], 50.f, 20, FColor::Blue, false, 60.f);
	}
}
