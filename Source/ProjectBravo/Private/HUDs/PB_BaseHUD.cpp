// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDs/PB_BaseHUD.h"
#include "UMGs/GameplayWidgets/PB_CoreWidget.h"
#include "Kismet/KismetSystemLibrary.h"


void APB_BaseHUD::BeginPlay()
{
	Super::BeginPlay();
}

void APB_BaseHUD::InitHUD()
{

	/* Focus input on the game */
	FInputModeGameOnly InputMode;
	this->GetOwningPlayerController()->SetInputMode(InputMode);
	this->GetOwningPlayerController()->SetShowMouseCursor(false);

	if (CoreWidgetClass)
	{
		if (CoreWidgetInstance = CreateWidget<UPB_CoreWidget>(this->GetWorld(), CoreWidgetClass))
		{
			CoreWidgetInstance->AddToViewport();
		}
	}
}

void APB_BaseHUD::ClearHUD()
{
	if (CoreWidgetInstance)
	{
		CoreWidgetInstance->RemoveFromParent();
		CoreWidgetInstance = nullptr;
	}
}
