// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_CharacterBase.h"
#include "C_PlayerCharacter.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UWidgetComponent;

// Player Character Base
UCLASS()
class ASSIGNMENT6_API AC_PlayerCharacter : public AC_CharacterBase
{
	GENERATED_BODY()

public:
	//AC_PlayerCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	AC_PlayerCharacter();

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void WidgetInvisible(bool val);

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	void OnDeath();
	void UpdateWidget();

protected:
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);

	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser
	) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<UCameraComponent> CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	// UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = UI)
	// TObjectPtr<UWidgetComponent> WidgetComponent;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;
};
