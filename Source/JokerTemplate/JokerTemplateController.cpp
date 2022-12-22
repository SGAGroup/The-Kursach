// Fill out your copyright notice in the Description page of Project Settings.

#include "JokerTemplateController.h"
#include "GameFramework/Pawn.h"
#include "JokerTemplateCharacter.h"

AJokerTemplateController::AJokerTemplateController()
{
	// Дефолтные настройки контроллера
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AJokerTemplateController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bIsShooting)
	{
		FVector HitLocation = FVector::ZeroVector;
		FHitResult Hit;

		// Получение места клика на экране
		GetHitResultUnderCursor(ECC_Visibility, true, Hit);

		HitLocation = Hit.Location;

		APawn* const MyPawn = GetPawn();
		FVector HitLocationToPlayer = HitLocation - MyPawn->GetActorLocation();

		// Поворот в нужном направлении
		if (MyPawn)
		{
			FRotator Rotation = FRotator::ZeroRotator;

			Rotation.Yaw = HitLocationToPlayer.Rotation().Yaw;

			MyPawn->SetActorRotation(Rotation);
		}
	}
}

void AJokerTemplateController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("Shoot", IE_Pressed, this, &AJokerTemplateController::Shoot);
	InputComponent->BindAction("Shoot", IE_Released, this, &AJokerTemplateController::StopShooting);
}


void AJokerTemplateController::Shoot()
{
	bIsShooting = true;

}

void AJokerTemplateController::StopShooting()
{
	bIsShooting = false;

}
