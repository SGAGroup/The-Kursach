// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JokerTemplateGameMode.generated.h"

UCLASS(minimalapi)
class AJokerTemplateGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJokerTemplateGameMode();
	UPROPERTY(EditAnywhere, Category = "Spawn")
		TSubclassOf<class AMedBag> FirstAidBlueprint;
	float spawnAidTimer;
	virtual void Tick(float DeltaTime) override;
	FVector GenerateRandomLocation();
};



