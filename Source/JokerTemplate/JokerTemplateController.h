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

	// ��������
	void Shoot();
	void StopShooting();


	//// ������� �� ���
	//void LMBPressed();
	//
	//// ���������� ���
	//void LMBReleased();

private:
	bool bIsShooting;
};
