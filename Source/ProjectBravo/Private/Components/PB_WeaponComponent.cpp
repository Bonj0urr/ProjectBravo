// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PB_WeaponComponent.h"
#include "Weapons/PB_BaseWeapon.h"

UPB_WeaponComponent::UPB_WeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPB_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UPB_WeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UPB_WeaponComponent::InitPrimaryWeapon(UPB_WeaponDataAsset* WeaponData)
{
}

void UPB_WeaponComponent::InitSecondaryWeapon(UPB_WeaponDataAsset* WeaponData)
{
}

void UPB_WeaponComponent::SwitchWeapon()
{
}

void UPB_WeaponComponent::ShootCurrentWeapon()
{
	Server_ShootCurrentWeapon();
}

void UPB_WeaponComponent::Server_ShootCurrentWeapon_Implementation()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Shoot();
	}
}

void UPB_WeaponComponent::ReloadCurrentWeapon()
{
}


