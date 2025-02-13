// Fill out your copyright notice in the Description page of Project Settings.


#include "C_RandomItem.h"
#include "Components/BoxComponent.h"
#include "C_ItemSpawnRow.h"


// Sets default values
AC_RandomItem::AC_RandomItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene"); 
	SetRootComponent(SceneComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Box");
	BoxComponent->SetupAttachment(SceneComponent);


}

FVector AC_RandomItem::GetRandomPointVolume()
{
	FVector BoxExtent = BoxComponent->GetScaledBoxExtent(); //박스 크기의    반지름
	FVector BoxOrigin = BoxComponent->GetComponentLocation();

	return BoxOrigin + FVector(
		FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
		FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
		FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
	);
}

FItemSpawnRow* AC_RandomItem::GetRandomItem() const
{
	if (!RandomItem) return nullptr;

	TArray<FItemSpawnRow*> AllRows;

	static const FString ContextString = TEXT("ItemSpawnFailed");
	RandomItem->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return nullptr;

	float TotalChance = 0.0f;

	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandVal = FMath::FRandRange(0, TotalChance);
	float AccumulateChance = 0.0f;

	for (FItemSpawnRow* Row : AllRows)
	{
		AccumulateChance += Row->SpawnChance;
		if (RandVal <= AccumulateChance)
			return Row;
	}

	return nullptr;
}

AActor* AC_RandomItem::SpawnRandomItem()
{
	if (FItemSpawnRow* SelectedRow = GetRandomItem())
	{
		if (UClass* ActualClass = SelectedRow->ItemClass.Get())
		{
			return SpawnItem(ActualClass);
		}
	}

	return nullptr;
}

AActor* AC_RandomItem::SpawnItem(TSubclassOf<AActor> ItemClass)
{
	auto SpawnedItem = GetWorld()->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointVolume(),
		FRotator::ZeroRotator
	);

	/*UWorld* world = GetWorld();

	AActor* SpawnedItem = world->SpawnActor<AActor>(
		ItemClass,
		GetRandomPointVolume(),
		FRotator::ZeroRotator
	);*/

	return SpawnedItem;
}

// Called when the game starts or when spawned
void AC_RandomItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_RandomItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

