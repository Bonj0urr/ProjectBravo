// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "PB_BaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UPB_HealthComponent;
class UPB_WeaponComponent;
class APB_BasePlayerController;

UCLASS()
class PROJECTBRAVO_API APB_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APB_BaseCharacter();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UPB_HealthComponent* GetHealthComponent() const { return HealthComponent; }

	UFUNCTION()
	void Die();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void BeginPlay();

	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION()
	AActor* ShootTrace();

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void Shoot(const FInputActionValue& Value);
	
	UFUNCTION(Server, Reliable)
	void Server_Shoot();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_Die();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PB|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PB|Camera", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPB_HealthComponent> HealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PB|Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPB_WeaponComponent> WeaponComponent;

	UPROPERTY()
	FTimerHandle RespawnDelayTimer;
	
	UPROPERTY()
	FTimerHandle InitUIDelayTimer;
};
