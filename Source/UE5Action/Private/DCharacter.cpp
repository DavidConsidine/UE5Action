// Fill out your copyright notice in the Description page of Project Settings.


#include "DCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Blueprint/UserWidget.h"
#include "Components/Widget.h"
#include "DBaseProjectile.h"
#include "DAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

ADCharacter::ADCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);

	InteractionComp = CreateDefaultSubobject<UDInteractionComponent>("InteractionComp");
	
	GetCharacterMovement()->bOrientRotationToMovement = true;

	AttrComp = CreateDefaultSubobject<UDAttributeComponent>(TEXT("AttrComp"));

	bUseControllerRotationYaw = false;

	ProjectileTrace = 5000.f;

	TimeToHitParamName = "TimeToHit";
	HandSocketName = "Muzzle_01";
}

void ADCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	AttrComp->OnHealthChanged.AddDynamic(this, &ADCharacter::OnHealthChanged);
}

void ADCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADCharacter::MoveForward(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;
	AddMovementInput(ControlRotation.Vector(), Value);
}

void ADCharacter::MoveRight(float Value)
{
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f;
	ControlRotation.Roll = 0.f;

	FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);

	AddMovementInput(RightVector, Value);
}

void ADCharacter::PrimaryAttack()
{
	StartAttackEffects();
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ThisClass::PrimaryAttack_TimeElapsed, 0.2f);
}

void ADCharacter::SecondaryAttack()
{
	StartAttackEffects();

	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &ThisClass::SecondaryAttack_TimeElapsed, 0.2f);
}

void ADCharacter::StartAttackEffects()
{
	PlayAnimMontage(AttackAnim);
	UGameplayStatics::SpawnEmitterAttached(CastingEffect, GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);
}

void ADCharacter::Teleport()
{
	StartAttackEffects();

	GetWorldTimerManager().SetTimer(TimerHandle_Teleport, this, &ThisClass::Teleport_TimeElapsed, 0.2f);
}

void ADCharacter::PrimaryInteract()
{
	if (InteractionComp)
	{
		InteractionComp->PrimaryInteract();
	}
}

void ADCharacter::TryToJump()
{
	if (CanJump())
	{
		Jump();
	}
}

void ADCharacter::PrimaryAttack_TimeElapsed()
{
	//check()
	//ensure()
	//ensureAlways()
	if (ensureAlways(PrimaryProjectileClass))
	{
		LaunchProjectile(PrimaryProjectileClass);
	}
}

void ADCharacter::SecondaryAttack_TimeElapsed()
{
	if (ensureAlways(SecondaryProjectileClass))
	{
		LaunchProjectile(SecondaryProjectileClass);
	}
}

void ADCharacter::Teleport_TimeElapsed()
{
	if (ensureAlways(TeleportProjectileClass))
	{
		LaunchProjectile(TeleportProjectileClass);
	}
}

void ADCharacter::OnHealthChanged(AActor* InstigatorActor, UDAttributeComponent* owningComp, float NewHealth, float Delta)
{
	if (Delta < 0.f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);
	}

	if (NewHealth <= 0.f && Delta < 0.f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		if (PC != nullptr)
		{
			DisableInput(PC);
		}
	}
}

void ADCharacter::LaunchProjectile(TSubclassOf<AActor>& Projectile)
{
	if (ensure(Projectile))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.f);

		// Ignore the player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComp->GetComponentLocation();

		// endpoint far into the look-at distance (not too far, still adjust somewhat towards crosshair on a miss)
		FVector TraceEnd = CameraComp->GetComponentLocation() + (GetControlRotation().Vector() * 5000);
		
		FHitResult Hit;
		// returns true if we got to a blocking hit
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			// Overwrite trace end with impact point in world
			TraceEnd = Hit.ImpactPoint;
		}

		// find new direction/rotation from Hand pointing to impact point in world.
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(Projectile, SpawnTM, SpawnParams);
	}
}


void ADCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// -- Rotation Visualization -- //
	const float DrawScale = 100.f;
	const float Thickness = 5.f;

	FVector LineStart = GetActorLocation();
	// Offset to the right of pawn
	LineStart += GetActorRightVector() * 100.f;
	// Set line end in direction of the acotr's forward direction
	FVector ActorDirection_LineEnd = LineStart + (GetActorForwardVector() * 100.f);
	// Draw Actor's Direction
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ActorDirection_LineEnd, DrawScale, FColor::Yellow, false, 0.f, 0, Thickness);

	FVector ControllerDirection_LineEnd = LineStart + (GetControlRotation().Vector() * 100.f);
	// Draw 'Controller' Rotation ('PlayerController' that possessed' this character)
	DrawDebugDirectionalArrow(GetWorld(), LineStart, ControllerDirection_LineEnd, DrawScale, FColor::Green, false, 0.f, 0, Thickness);
}

void ADCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ThisClass::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ThisClass::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &ThisClass::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &ThisClass::SecondaryAttack);
	PlayerInputComponent->BindAction("PrimaryInteract", IE_Pressed, this, &ThisClass::PrimaryInteract);
	PlayerInputComponent->BindAction("Teleport", IE_Pressed, this, &ThisClass::Teleport);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ThisClass::TryToJump);
}

void ADCharacter::HealSelf(float Amount /* = 100 */)
{
	AttrComp->ApplyHealthChange(this, Amount);
}

