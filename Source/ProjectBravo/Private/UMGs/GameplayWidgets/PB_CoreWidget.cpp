// Fill out your copyright notice in the Description page of Project Settings.


#include "UMGs/GameplayWidgets/PB_CoreWidget.h"
#include "Components/TextBlock.h"
#include "Characters/PB_BaseCharacter.h"
#include "Components/PB_HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"

void UPB_CoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APB_BaseCharacter* Owner = Cast<APB_BaseCharacter>(GetOwningPlayerPawn());
	if (!Owner)
	{
		return;
	}

	if (UPB_HealthComponent* HealthComponent = Owner->GetHealthComponent())
	{
		HealthComponent->OnHealthChangedDelegate.AddDynamic(this, &UPB_CoreWidget::UpdateHealth);
		HealthComponent->OnHealthChangedDelegate.Broadcast(HealthComponent->GetMaxHealth());
	}
}

void UPB_CoreWidget::UpdateHealth(int32 CurrentHealth)
{
	TextCurrentHealth->SetText(FText::FromString(FString::FromInt(CurrentHealth)));
}
