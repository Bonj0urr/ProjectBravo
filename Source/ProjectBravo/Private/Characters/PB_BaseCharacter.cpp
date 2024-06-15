// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PB_BaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/DamageEvents.h"
#include "Components/PB_HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameModes/PB_BaseGameMode.h"
#include "Controllers/PB_BasePlayerController.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Net/UnrealNetwork.h>

APB_BaseCharacter::APB_BaseCharacter()
{
	bReplicateUsingRegisteredSubObjectList = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	HealthComponent = CreateDefaultSubobject<UPB_HealthComponent>(TEXT("HealthComponent"));
}

void APB_BaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// TO DO check if this line even needed
	DOREPLIFETIME(APB_BaseCharacter, HealthComponent);
}

void APB_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	AddReplicatedSubObject(HealthComponent);
}

/* Occurs when new controller possesses this pawn (on server) */
void APB_BaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	APB_BasePlayerController* OwningPlayerController = Cast<APB_BasePlayerController>(this->GetController());
	if (OwningPlayerController)
	{
		/* Timer to avoid hud initialization bug */
		GetWorldTimerManager().SetTimer(
			InitUIDelayTimer,
			[OwningPlayerController]()
			{
				OwningPlayerController->Client_InitUI();
			},
			0.5f,
			false
		);
	}
}

void APB_BaseCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APB_BaseCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APB_BaseCharacter::Shoot(const FInputActionValue& Value)
{
	if (!Value.Get<bool>())
	{
		return;
	}

	AActor* HitActor = ShootTrace();
	if (!HitActor && !HitActor->ActorHasTag("Player"))
	{
		return;
	}

	Server_Shoot();
}

void APB_BaseCharacter::Server_Shoot_Implementation()
{
	AActor* HitActor = ShootTrace();
	if (HitActor)
	{
		HitActor->TakeDamage(20.0f, FDamageEvent(), this->GetController(), this);
	}
}

void APB_BaseCharacter::Multicast_Die_Implementation()
{
	if (UCapsuleComponent* Capsule = this->GetCapsuleComponent())
	{
		Capsule->DestroyComponent();
	}
	if (USkeletalMeshComponent* MeshComponent = this->GetMesh())
	{
		MeshComponent->SetSimulatePhysics(true);
	}

}

AActor* APB_BaseCharacter::ShootTrace()
{
	FVector CameraWorldLocation = GetFollowCamera()->GetComponentLocation();
	TArray<AActor*> IgnoreActors;
	FHitResult HitResult;

	UKismetSystemLibrary::LineTraceSingle(this, CameraWorldLocation,
		CameraWorldLocation + GetFollowCamera()->GetForwardVector() * 10000,
		TraceTypeQuery1, false, IgnoreActors, EDrawDebugTrace::ForDuration, HitResult, true);

	if (AActor* HitActor = HitResult.GetActor())
	{
		return HitActor;
	}
	return nullptr;
}

void APB_BaseCharacter::Die()
{
	if (APB_BasePlayerController* OwningPlayerController = Cast<APB_BasePlayerController>(this->GetController()))
	{
		OwningPlayerController->Client_RemoveUI();
	}

	Multicast_Die();

	/* Respawn dead player */
	GetWorldTimerManager().SetTimer(
		RespawnDelayTimer,
		[this]() 
		{ 
			if (APB_BaseGameMode* GameMode = Cast<APB_BaseGameMode>(UGameplayStatics::GetGameMode(this)))
			{
				GameMode->RespawnPlayer(this->GetController());
			}
		},
		2.0f, 
		false
	);
}

void APB_BaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APB_BaseCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APB_BaseCharacter::Look);

		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &APB_BaseCharacter::Shoot);
	}

}

