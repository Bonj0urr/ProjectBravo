// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/PB_BaseWeapon.h"
#include "DataAssets/PB_WeaponDataAsset.h"

APB_BaseWeapon::APB_BaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APB_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();

}

void APB_BaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APB_BaseWeapon::InitWeapon(UPB_WeaponDataAsset* WeaponData)
{
	if (WeaponData)
	{
		WeaponMesh = WeaponData->WeaponMesh;
		ProjectileClass = WeaponData->ProjectileClass;
		FireRate = WeaponData->FireRate;
		ClipAmmoCount = WeaponData->ClipAmmoCount;
		ReserveAmmoCount = WeaponData->ReserveAmmoCount;
	}
}

void APB_BaseWeapon::Shoot()
{

}

void APB_BaseWeapon::Reload()
{

}



