// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "C_RandomItem.generated.h"
struct FItemSpawnRow;
class UBoxComponent;

UCLASS()
class ASSIGNMENT6_API AC_RandomItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_RandomItem();

	FVector GetRandomPointVolume();

	FItemSpawnRow* GetRandomItem() const;

	UFUNCTION(BlueprintCallable)
	AActor* SpawnRandomItem();

	UFUNCTION(BlueprintCallable)
	AActor* SpawnItem(TSubclassOf<AActor> ItemClass);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "BoxComp")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* RandomItem;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
