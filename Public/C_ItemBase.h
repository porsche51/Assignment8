// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemInterface.h"
#include "GameFramework/Actor.h"
#include "C_ItemBase.generated.h"
class USphereComponent;

UCLASS()
class ASSIGNMENT6_API AC_ItemBase : public AActor, public IItemInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_ItemBase();

	UFUNCTION()
	virtual void OnItemOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OverlapActor,
	UPrimitiveComponent* OverlapComp,
	int32 OtherActorIndex,
	bool bFromSweep,
	const FHitResult& SweepResult
	);

	UFUNCTION()
	virtual void OnItemEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OverlapActor,
	UPrimitiveComponent* OverlapComp,
	int32 OtherActorIndex
	);

	virtual void ActivateItem(AActor* Activator);

	virtual FName GetItemType() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StaticMeshComp")
	UStaticMeshComponent* StaticMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SphereComp")
	USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	virtual void DestroyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
