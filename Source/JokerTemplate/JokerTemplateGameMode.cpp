// Copyright Epic Games, Inc. All Rights Reserved.

#include "JokerTemplateGameMode.h"
#include "JokerTemplateController.h"
#include "JokerTemplateCharacter.h"
#include "MedBag.h"
#include "UObject/ConstructorHelpers.h"

AJokerTemplateGameMode::AJokerTemplateGameMode()
{
	// set default pawn class to our Blueprinted character
	PrimaryActorTick.bCanEverTick = true;
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));

	// ��������� ���������� ������ �����������
	PlayerControllerClass = AJokerTemplateController::StaticClass();

	// ��������� ���������� pawn ������ ��������� ���������
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_JokerTemplateCharacter"));
	/*if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	*/

	// ��������� ���������� ����������� ��������� �����������
	/*static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_JokerTemplateController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}*/
}
void AJokerTemplateGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	spawnAidTimer -= DeltaTime;
	if (spawnAidTimer < 0.0f)
	{
		float NumberOfSecondsBetweenSpawn = 1.0f;
		spawnAidTimer = NumberOfSecondsBetweenSpawn;
		UWorld* world = GetWorld();
		if (world)
		{
			FVector firstAidLocation = GenerateRandomLocation();
			AMedBag* firstaid = world->SpawnActor<AMedBag>(FirstAidBlueprint, firstAidLocation, FRotator::ZeroRotator);
		}
	}

}

FVector AJokerTemplateGameMode::GenerateRandomLocation()
{
	FVector location;
	float minimum = 1;
	float maximum = 1000;
	location.X = FMath::RandRange(minimum, maximum);
	location.Y = FMath::RandRange(minimum, maximum);
	location.Z = 20;
	return location;
}