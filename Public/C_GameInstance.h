// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "C_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT6_API UC_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int Score;
	bool bIsGameStarted;

	int GetPoint() { return Score; }
	void AddScore(int Value);
	

};
