// Copyright Epic Games, Inc. All Rights Reserved.

#include "JokerTemplateGameMode.h"
#include "JokerTemplateController.h"
#include "JokerTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJokerTemplateGameMode::AJokerTemplateGameMode()
{
	// ��������� ���������� ������ �����������
	PlayerControllerClass = AJokerTemplateController::StaticClass();

	// ��������� ���������� pawn ������ ��������� ���������
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_JokerTemplateCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// ��������� ���������� ����������� ��������� �����������
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_JokerTemplateController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
