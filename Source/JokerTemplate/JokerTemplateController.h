// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JokerTemplateController.generated.h"

/**
 * 
 */
UCLASS()
class JOKERTEMPLATE_API AJokerTemplateController : public APlayerController
{
	GENERATED_BODY()


public:

	AJokerTemplateController();


protected:

	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	// Стрельба
	void Shoot();
	void StopShooting();


	//// Нажатие на лкм
	//void LMBPressed();
	//
	//// Отпускание лкм
	//void LMBReleased();

private:
	bool bIsShooting;
};
