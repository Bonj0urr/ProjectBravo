// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PB_BasePlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class PROJECTBRAVO_API APB_BasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Client, Reliable)
	void Client_RemoveUI();

	UFUNCTION(Client, Reliable)
	void Client_InitUI();

protected:
	virtual void BeginPlay();
	

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;
};
