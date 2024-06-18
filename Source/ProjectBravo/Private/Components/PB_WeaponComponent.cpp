// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/PB_WeaponComponent.h"

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

