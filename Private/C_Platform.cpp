// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Platform.h"

// Sets default values
AC_Platform::AC_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

}

// Called when the game starts or when spawned
void AC_Platform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveEvent();

}

void AC_Platform::LinearMovement(const FVector& StarterLocation, const FVector& Direction, float Speed, float Amplitude)
{
	FVector NewPos = StarterLocation + (Amplitude * Direction) + (Direction * Amplitude * sin(Speed * GetWorld()->GetTimeSeconds()));
	SetActorLocation(NewPos);
}

