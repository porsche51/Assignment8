// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "C_Pawn.generated.h"
class UCapsuleComponent;
class USpringArmComponent;
class UCameraComponent;


UCLASS()
class ASSIGNMENT6_API AC_Pawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AC_Pawn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;


	UFUNCTION()
	void Move(const FInputActionValue& value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float speed = 10;
	
	UFUNCTION()
	void Look(const FInputActionValue& value);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
