// Copyright Epic Games, Inc. All Rights Reserved.

#include "JokerTemplateGameMode.h"
#include "JokerTemplateCharacter.h"
#include "FirstAid.h"
#include "UObject/ConstructorHelpers.h"

AJokerTemplateGameMode::AJokerTemplateGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
AJokerTemplateGameMode ::AJokerTemplateGameMode() :Super()
{
	PrimaryActorTick.bCanEverTick = true;
 }
void AJokerTemplateGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	spawnAidTimer -= DeltaTime;
	if (spawnAidTimer < 0.0f)
	{
		float NumberOfSecondsBetweenSpawn = 10.0f;
		spawnAidTimer = NumberOfSecondsBetweenSpawn;
		UWorld* world = GetWorld();
		if (world)
		{
			FVector firstAidLocation = GenerateRandomLocation();
			AFirstAid* firstaid = world->SpawnActor<AFirstAid>(FirstAidBlueprint, firstAidLocation, FRotator::ZeroRotator);
		}
	}

}

FVector AJokerTemplateGameMode::GenerateRandomLocation()
{
	FVector location;
	float minimum = 100;
	float maximum = 1000;
	location.X = FMath::RandRange(minimum, maximum);
	location.Y = FMath::RandRange(minimum, maximum);
	location.Z = 0;
	return location;
}