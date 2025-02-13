// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Coin.h"
#include "C_Gamestatebase.h"
#include "C_GameInstance.h"

AC_Coin::AC_Coin()
{
    PointValue = 10;
}

void AC_Coin::ActivateItem(AActor* Activator)
{
    if (UWorld* World = GetWorld())
    {
        if (UC_GameInstance* Gamestatebase = World->GetGameInstance<UC_GameInstance>())
        {
            Gamestatebase->AddScore(PointValue);
            // Gamestatebase->OnCoinCollected();
            DestroyItem();
        }
    }
}
