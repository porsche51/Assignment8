// Fill out your copyright notice in the Description page of Project Settings.


#include "C_ItemBase.h"
#include "Components/SphereComponent.h"

// Sets default values
AC_ItemBase::AC_ItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Scene");  // 함수 호출
	SetRootComponent(SceneComponent);

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere");
	SphereComponent->SetupAttachment(SceneComponent);

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMeshComponent->SetupAttachment(SphereComponent);

	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AC_ItemBase::OnItemOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this, &AC_ItemBase::OnItemEndOverlap);
}

void AC_ItemBase::OnItemOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OverlapActor,
	UPrimitiveComponent* OverlapComp, int32 OtherActorIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlapActor && OverlapActor->ActorHasTag("Player"))
	{
		ActivateItem(OverlapActor);
	}
}

void AC_ItemBase::OnItemEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OverlapActor,
	UPrimitiveComponent* OverlapComp, int32 OtherActorIndex)
{
	
}

void AC_ItemBase::ActivateItem(AActor* Activator)
{
}

FName AC_ItemBase::GetItemType() const
{
	return FName();
}

void AC_ItemBase::DestroyItem()
{
	Destroy();
}

// Called when the game starts or when spawned
void AC_ItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_ItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

