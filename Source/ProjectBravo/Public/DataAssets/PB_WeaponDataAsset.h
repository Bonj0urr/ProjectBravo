// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PB_WeaponDataAsset.generated.h"

class APB_BaseProjectile;

UCLASS()
class PROJECTBRAVO_API UPB_WeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    TObjectPtr<UStaticMeshComponent> WeaponMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    TSubclassOf<APB_BaseProjectile> ProjectileClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    float FireRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    int32 ClipAmmoCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    int32 ReserveAmmoCount;

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    USoundBase* FireSound;*/

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    UParticleSystem* MuzzleFlash;*/

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Weapon")
    TObjectPtr<UAnimationAsset> FireAnimation;*/
	
};
