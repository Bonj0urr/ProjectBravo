// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PB_HealthComponent.h"
#include "Characters/PB_BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"
#include <Net/UnrealNetwork.h>

UPB_HealthComponent::UPB_HealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHealth = 100;
	CurrentHealth = MaxHealth;
}

void UPB_HealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPB_HealthComponent, CurrentHealth);
}

void UPB_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	this->GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UPB_HealthComponent::DamageTaken);
}

void UPB_HealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UPB_HealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage > 0.0f)
	{
		if (APB_BaseCharacter* OwnerCharacter = Cast<APB_BaseCharacter>(this->GetOwner()))
		{
			CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MaxHealth);

			/* Taking into account the host's character*/
			if (OwnerCharacter->IsLocallyControlled())
			{
				OnHealthChangedDelegate.Broadcast(CurrentHealth);
			}

			if (CurrentHealth <= 0)
			{
				OwnerCharacter->Die();
			}
		}
	}
}

void UPB_HealthComponent::OnRep_CurrentHealthChanged()
{
	OnHealthChangedDelegate.Broadcast(CurrentHealth);
}
