// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "C_ItemBase.h"
#include "C_Coin.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT6_API AC_Coin : public AC_ItemBase
{
	GENERATED_BODY()
	
public:

    AC_Coin();

    virtual void ActivateItem(AActor* Activator) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
    int PointValue;

};
