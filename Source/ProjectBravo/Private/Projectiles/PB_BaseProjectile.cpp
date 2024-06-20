// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/PB_BaseProjectile.h"

APB_BaseProjectile::APB_BaseProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APB_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void APB_BaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

