// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_ItemBase.h"
#include "C_Heal.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT6_API AC_Heal : public AC_ItemBase
{
	GENERATED_BODY()

public:

    AC_Heal();

    virtual void ActivateItem(AActor* Activator) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int HealAmount;

};
