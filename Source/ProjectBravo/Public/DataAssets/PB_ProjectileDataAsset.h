// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PB_ProjectileDataAsset.generated.h"


UCLASS()
class PROJECTBRAVO_API UPB_ProjectileDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Projectile")
    TObjectPtr<UStaticMeshComponent> ProjectileMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Projectile")
    float Damage;

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Projectile")
    USoundBase* ExplosionRadius;*/

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Projectile")
    UParticleSystem* ExplosionEffect;*/

    /*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PB|Projectile")
    TObjectPtr<UAnimationAsset> ExplodeAnimation;*/
};
