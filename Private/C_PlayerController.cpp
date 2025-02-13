// Fill out your copyright notice in the Description page of Project Settings.


#include "C_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "C_Gamestatebase.h"
#include "Components/TextBlock.h"
#include "C_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "C_PlayerCharacter.h"

AC_PlayerController::AC_PlayerController()
{

}

void AC_PlayerController::ShowMainGame()
{
    ClearAllWidget();

    if (!MainGameWidgetClass) return;

    MainGameWidget = CreateWidget<UUserWidget>(this, MainGameWidgetClass);

    if (MainGameWidget)
    {
        MainGameWidget->AddToViewport();
        bShowMouseCursor = false;
        SetInputMode(FInputModeGameOnly());
    }

    if (AC_Gamestatebase* GameState = GetWorld() ? GetWorld()->GetGameState<AC_Gamestatebase>() : nullptr)
    {
        GameState->UpdateHUD();
    }

    if (AC_PlayerCharacter* C_Character = Cast<AC_PlayerCharacter>(GetPawn()))
    {
        C_Character->WidgetInvisible(true);
    }
}

void AC_PlayerController::ShowGameOver()
{
    ClearAllWidget();

    if (!GameOverMenuWidgetClass) return;

    GameOverMenuWidget = CreateWidget<UUserWidget>(this, GameOverMenuWidgetClass);
    if (!GameOverMenuWidget) return;

    GameOverMenuWidget->AddToViewport();
    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly());
}

void AC_PlayerController::MoveToMainMenu()
{
    if (UC_GameInstance* GameInstance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance()))
    {
        GameInstance->bIsGameStarted = false;
    }

    ShowMainMenu();

    UGameplayStatics::OpenLevel(GetWorld(), FName("L_MainMenu"));
}

UUserWidget* AC_PlayerController::GetHUDWidget()
{
    return MainGameWidget;
}

void AC_PlayerController::ClearAllWidget()
{
    if (MainGameWidget)
    {
        MainGameWidget->RemoveFromParent();
        MainGameWidget = nullptr;
    }

    if (MainMenuWidget)
    {
        MainMenuWidget->RemoveFromParent();
        MainMenuWidget = nullptr;
    }

    if (GameOverMenuWidget)
    {
        GameOverMenuWidget->RemoveFromParent();
        GameOverMenuWidget = nullptr;
    }
}

void AC_PlayerController::StartGame()
{  
    if (UC_GameInstance* GameInstance = Cast<UC_GameInstance>(GetWorld()->GetGameInstance()))
    {
        GameInstance->Score = 0;
        GameInstance->bIsGameStarted = false;
    }

    SetPause(false);
    UGameplayStatics::OpenLevel(GetWorld(), FName("L_Main"));
}

void AC_PlayerController::BeginPlay()
{
    if (ULocalPlayer* player = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = player->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
        {
            if (MappingContext)
            {
                Subsystem->AddMappingContext(MappingContext, 0);
            }
        }
    }

    FString CurrentMapName = GetWorld()->GetMapName();

    if (CurrentMapName.Contains("L_MainMenu"))
    {
        ShowMainMenu();
    }
    else
    {
        ShowMainGame();
    }
}

void AC_PlayerController::ShowMainMenu()
{
    ClearAllWidget();

    if (!MainMenuWidgetClass) return;

    MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
    if (MainMenuWidget == nullptr) return;

    MainMenuWidget->AddToViewport();
    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly());

    if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidget->GetWidgetFromName(TEXT("StartButtonText"))))
    {
        ButtonText->SetText(FText::FromString(TEXT("Start")));
    }

    if (AC_PlayerCharacter* C_Character = Cast<AC_PlayerCharacter>(GetPawn()))
    {
        C_Character->WidgetInvisible(false);
    }
}