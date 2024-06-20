// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PB_WeaponComponent.generated.h"

class APB_BaseWeapon;
class UPB_WeaponDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTBRAVO_API UPB_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPB_WeaponComponent();

public:
    UFUNCTION()
    void InitPrimaryWeapon(UPB_WeaponDataAsset* WeaponData);

    UFUNCTION()
    void InitSecondaryWeapon(UPB_WeaponDataAsset* WeaponData);

    /* Switch weapon methods */
    UFUNCTION()
    void SwitchWeapon();

    UFUNCTION(Server, Reliable)
    void Server_SwitchCurrentWeapon();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_SwitchCurrentWeapon();

    /* Shoot current weapon methods */
    UFUNCTION()
    void ShootCurrentWeapon();

    UFUNCTION(Server, Reliable)
    void Server_ShootCurrentWeapon();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ShootCurrentWeapon();

    /* Reload current weapon methods */
    UFUNCTION()
    void ReloadCurrentWeapon();

    UFUNCTION(Server, Reliable)
    void Server_ReloadCurrentWeapon();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_ReloadCurrentWeapon();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
    UPROPERTY()
    TObjectPtr<APB_BaseWeapon> CurrentWeapon;

    UPROPERTY()
    TObjectPtr<APB_BaseWeapon> PrimaryWeapon;

    UPROPERTY()
    TObjectPtr<APB_BaseWeapon> SecondaryWeapon;

    UPROPERTY()
    bool bIsPrimaryEquipped;
};
