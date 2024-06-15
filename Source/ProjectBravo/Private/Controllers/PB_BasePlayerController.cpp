// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/PB_BasePlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "HUDs/PB_BaseHUD.h"
#include "Kismet/KismetSystemLibrary.h"


void APB_BasePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(this->GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}

void APB_BasePlayerController::Client_InitUI_Implementation()
{
	if (!this->IsLocalPlayerController())
	{
		return;
	}

	if (APB_BaseHUD* ClientHUD = Cast<APB_BaseHUD>(this->GetHUD()))
	{
		UKismetSystemLibrary::PrintString(this, "Client_InitUI_Implementation call");
		ClientHUD->InitHUD();
	}
}

void APB_BasePlayerController::Client_RemoveUI_Implementation()
{
	if (!this->IsLocalPlayerController())
	{
		return;
	}

	if (APB_BaseHUD* ClientHUD = Cast<APB_BaseHUD>(this->GetHUD()))
	{
		ClientHUD->ClearHUD();
	}
}
