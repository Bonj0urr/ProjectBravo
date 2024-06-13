// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/PB_BaseGameMode.h"
#include "Characters/PB_BaseCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

void APB_BaseGameMode::RespawnPlayer(AController* PlayerController)
{
	if (PlayerController)
	{
		if (APawn* PlayerPawn = PlayerController->GetPawn())
		{
			PlayerPawn->Destroy();
			SpawnPlayer(PlayerController);
		}
	}
}

void APB_BaseGameMode::SpawnPlayer(AController* PlayerController)
{
	if (PlayerController)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		if (AActor* PlayerStart = ChoosePlayerStart(PlayerController))
		{
			if (APawn* NewPlayerPawn = GetWorld()->
				SpawnActor<APawn>(SpawnCharacterClass, PlayerStart->GetActorTransform(), SpawnParams))
			{
				UKismetSystemLibrary::PrintString(this, "spawn successfully called");

				PlayerController->Possess(NewPlayerPawn);
			}
		}
	}
}
