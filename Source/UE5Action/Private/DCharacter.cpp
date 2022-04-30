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
	PlayAnimMontage(AttackAnim);
	
	GetWorldTimerManager().SetTimer(TimerHandle_PrimaryAttack, this, &ThisClass::PrimaryAttack_TimeElapsed, 0.2f);
}

void ADCharacter::SecondaryAttack()
{
	PlayAnimMontage(AttackAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_SecondaryAttack, this, &ThisClass::SecondaryAttack_TimeElapsed, 0.2f);
}

void ADCharacter::Teleport()
{
	PlayAnimMontage(AttackAnim);

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
		FHitResult Hit;
		LaunchProjectile(PrimaryProjectileClass, Hit);
	}
}

void ADCharacter::SecondaryAttack_TimeElapsed()
{
	if (ensureAlways(SecondaryProjectileClass))
	{
		FHitResult Hit;
		LaunchProjectile(SecondaryProjectileClass, Hit);
	}
}

void ADCharacter::Teleport_TimeElapsed()
{
	if (ensureAlways(TeleportProjectileClass))
	{
		FHitResult Hit;
		LaunchProjectile(TeleportProjectileClass, Hit);
	}
}

void ADCharacter::LaunchProjectile(TSubclassOf<AActor>& Projectile, FHitResult& Hit)
{
	APlayerController* MyController = Cast<APlayerController>(GetController());
	if (MyController)
	{
		FVector2D ViewportSize;
		FVector TraceStart;
		FVector TraceDirection;

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);

		GetWorld()->GetGameViewport()->GetViewportSize(ViewportSize);
		MyController->DeprojectScreenPositionToWorld((ViewportSize.X / 2.f), (ViewportSize.Y / 2.f), TraceStart, TraceDirection);

		FVector TraceEnd = TraceStart + (TraceDirection * ProjectileTrace);
		bool bBlockingHit = GetWorld()->LineTraceSingleByObjectType(Hit, TraceStart, TraceEnd, ObjectQueryParams);
		FVector EndLocation = bBlockingHit ? Hit.ImpactPoint : TraceEnd;

		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 10.f, 0, 1.f);
		//DrawDebugLine(GetWorld(), TraceStart, EndLocation, FColor::Blue, false, 10.f, 0, 1.f);
		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");
		FRotator HandRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, EndLocation);

		FTransform SpawnTM = FTransform(HandRotation, HandLocation);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
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

