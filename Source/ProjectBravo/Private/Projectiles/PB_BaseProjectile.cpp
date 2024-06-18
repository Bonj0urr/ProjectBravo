// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectiles/PB_BaseProjectile.h"

// Sets default values
APB_BaseProjectile::APB_BaseProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APB_BaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APB_BaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

