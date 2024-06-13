// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PB_BaseGameMode.generated.h"

class APB_BaseCharacter;

UCLASS()
class PROJECTBRAVO_API APB_BaseGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void RespawnPlayer(AController* PlayerController);

	void SpawnPlayer(AController* PlayerController);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|DefaultClasses")
	TSubclassOf<APB_BaseCharacter> SpawnCharacterClass;
};
