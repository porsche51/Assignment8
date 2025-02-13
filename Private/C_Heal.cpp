// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Heal.h"
#include "C_PlayerCharacter.h"

AC_Heal::AC_Heal()
{
    HealAmount = 10;
}

void AC_Heal::ActivateItem(AActor* Activator)
{
    if (AC_PlayerCharacter* Player = Cast<AC_PlayerCharacter>(Activator))
    {
        Player->AddHealth(HealAmount);
        DestroyItem();
    }
}
