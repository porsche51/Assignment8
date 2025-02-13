// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "C_PlayerController.generated.h"
class UInputAction;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class ASSIGNMENT6_API AC_PlayerController : public APlayerController
{
	GENERATED_BODY()


public:

	AC_PlayerController();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputMappingContext* MappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> MainGameWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UUserWidget* MainGameWidget;

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowMainGame();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	void ShowGameOver();

	UFUNCTION(BlueprintCallable)
	void MoveToMainMenu();

	UFUNCTION(BlueprintCallable, Category = "HUD")
	UUserWidget* GetHUDWidget();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UUserWidget* MainMenuWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UUserWidget> GameOverMenuWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "HUD")
	UUserWidget* GameOverMenuWidget;

	UFUNCTION(BlueprintCallable, Category = "Menu")
	void ShowMainMenu();

	void ClearAllWidget();

	UFUNCTION(BlueprintCallable)
	void StartGame();

	virtual void BeginPlay() override;
	
};
