// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "C_Gamestatebase.generated.h"
class AC_RandomItem;
class UDataTable;

/**
 * 
 */
UCLASS()
class ASSIGNMENT6_API AC_Gamestatebase : public AGameStateBase
{
	GENERATED_BODY()

public:

	AC_Gamestatebase();

	FTimerHandle WaveTimerHandle;
	FTimerHandle HUDTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float WaveDelay;
	
	void StartWave();

	void BeginPlay() override;

	void UpdateHUD();
	
	void OnGameOver();

	int Wave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UDataTable*> ItemSpawnRows;

private:

	
};
