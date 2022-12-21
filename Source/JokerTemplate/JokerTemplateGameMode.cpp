// Copyright Epic Games, Inc. All Rights Reserved.

#include "JokerTemplateGameMode.h"
#include "JokerTemplateCharacter.h"
#include "MedBag.h"
#include "UObject/ConstructorHelpers.h"

AJokerTemplateGameMode::AJokerTemplateGameMode()
{PrimaryActorTick.bCanEverTick = true;
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
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
	location.Z = 10;
	return location;
}