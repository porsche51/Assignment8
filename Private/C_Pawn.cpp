// Fill out your copyright notice in the Description page of Project Settings.


#include "C_Pawn.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "C_PlayerController.h"


// Sets default values
AC_Pawn::AC_Pawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	CapsuleComponent->InitCapsuleSize(5, 10);
	RootComponent = CapsuleComponent;
	

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMeshComponent->SetupAttachment(CapsuleComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(CapsuleComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);


}

void AC_Pawn::Move(const FInputActionValue& value)
{
	const FVector2D MoveInput = value.Get<FVector2D>();
	FVector MoveVector = FVector(MoveInput.X, MoveInput.Y, 0);
	FVector Direction = CameraComponent->GetForwardVector();
	FVector ActorLocation = GetActorLocation() + MoveVector * Direction * speed * GetWorld()->GetDeltaSeconds();
	SetActorLocation(ActorLocation);
}

void AC_Pawn::Look(const FInputActionValue& value)
{
	const FVector2D LookInput = value.Get<FVector2D>();
	FRotator LookRotator = FRotator(LookInput.Y, LookInput.X, 0);
	AddActorLocalRotation(LookRotator);
}

// Called when the game starts or when spawned
void AC_Pawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_Pawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AC_Pawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AC_PlayerController* PlayerController = Cast<AC_PlayerController>(GetController()))
		{
			EnhancedInputComponent->BindAction(
				PlayerController->MoveAction,
				ETriggerEvent::Triggered,
				this,
				&AC_Pawn::Move
			);

			EnhancedInputComponent->BindAction(
				PlayerController->LookAction,
				ETriggerEvent::Triggered,
				this,
				&AC_Pawn::Look
			);
		}
	}

}

