// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Gamestatebase.h"
#include "C_RandomItem.h"
#include "Kismet/GameplayStatics.h"
#include "C_ItemBase.h"
#include "C_PlayerController.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"
#include "C_GameInstance.h"

AC_Gamestatebase::AC_Gamestatebase()
{
	WaveDelay = 30.0f;
	Wave = -1;
}

void AC_Gamestatebase::StartWave()
{
	Wave += 1;

	if (Wave >= 3)
		return;

	TArray<AActor*> FoundItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_ItemBase::StaticClass(), FoundItems);

	for (auto item : FoundItems)
	{
		if (auto itemBase = Cast<AC_ItemBase>(item))
		{
			itemBase->DestroyItem();
		}
	}

	TArray<AActor*> RandomItems;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AC_RandomItem::StaticClass(), RandomItems);

	AC_RandomItem* Random = Cast<AC_RandomItem>(RandomItems[0]);
	
	Random->RandomItem = ItemSpawnRows[Wave];

	for (int i = 0; i <= 30; ++i) {
		Random->SpawnRandomItem();
	}

	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&AC_Gamestatebase::StartWave,
		WaveDelay,
		false
	);

}

void AC_Gamestatebase::BeginPlay()
{
	Super::BeginPlay();
	FString CurrentMapName = GetWorld()->GetMapName();

	if (!CurrentMapName.Contains("L_MainMenu"))
	{
		StartWave();
	}

	GetWorldTimerManager().SetTimer(
		HUDTimerHandle,
		this,
		&AC_Gamestatebase::UpdateHUD,
		0.1,
		true
	);
}


void AC_Gamestatebase::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		AC_PlayerController* SpartaPlayerController = Cast<AC_PlayerController>(PlayerController);
		{
			if (UUserWidget* HUDWidget = SpartaPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(WaveTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time: %.1f"), RemainingTime)));
				}
				
				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if (UGameInstance* GameInstance = GetGameInstance())
					{
						UC_GameInstance* C_GameInstance = Cast<UC_GameInstance>(GameInstance);
						if (C_GameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score: %d"), C_GameInstance->Score)));
						}
					}
				}

				if (UTextBlock* WaveIndexText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Wave"))))
				{
					WaveIndexText->SetText(FText::FromString(FString::Printf(TEXT("Wave: %d"), Wave + 1)));
				}
			}
		}
	}
}

void AC_Gamestatebase::OnGameOver()
{
	GetWorldTimerManager().ClearTimer(HUDTimerHandle);
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AC_PlayerController* C_PlayerController = Cast<AC_PlayerController>(PlayerController))
		{
			C_PlayerController->SetPause(true);
			C_PlayerController->ShowGameOver();
		}
	}
}
