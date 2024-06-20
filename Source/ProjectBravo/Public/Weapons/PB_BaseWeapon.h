// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PB_BaseWeapon.generated.h"

class UPB_WeaponDataAsset;
class APB_BaseProjectile;

UCLASS()
class PROJECTBRAVO_API APB_BaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	APB_BaseWeapon();

public:
	void InitWeapon(UPB_WeaponDataAsset* WeaponData);

	void Shoot();

	void Reload();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY()
    TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY()
    TSubclassOf<APB_BaseProjectile> ProjectileClass;

    float FireRate;

    int32 ClipAmmoCount;

    int32 ReserveAmmoCount;
};
