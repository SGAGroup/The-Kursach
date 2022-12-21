// Copyright Epic Games, Inc. All Rights Reserved.

#include "JokerTemplateGameMode.h"
#include "JokerTemplateController.h"
#include "JokerTemplateCharacter.h"
#include "UObject/ConstructorHelpers.h"

AJokerTemplateGameMode::AJokerTemplateGameMode()
{
	// Установка кастомного класса контроллера
	PlayerControllerClass = AJokerTemplateController::StaticClass();

	// Установка дефолтного pawn класса блюпринту персонажа
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_JokerTemplateCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// Установка дефолтного контроллера блюпринту контроллера
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_JokerTemplateController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
