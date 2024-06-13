// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PB_BaseHUD.generated.h"

class UPB_CoreWidget;

UCLASS()
class PROJECTBRAVO_API APB_BaseHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ClearHUD();

	void InitHUD();

protected:
	virtual void BeginPlay();

private:
	UPROPERTY()
	TObjectPtr<UPB_CoreWidget> CoreWidgetInstance;

	UPROPERTY(EditDefaultsOnly, Category = "PB|WidgetClass")
	TSubclassOf<UPB_CoreWidget> CoreWidgetClass;
};
