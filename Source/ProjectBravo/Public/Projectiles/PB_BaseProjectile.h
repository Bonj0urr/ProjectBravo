// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PB_BaseProjectile.generated.h"

UCLASS()
class PROJECTBRAVO_API APB_BaseProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	APB_BaseProjectile();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
