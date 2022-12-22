// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MapGenerator.generated.h"

UCLASS()
class JOKERTEMPLATE_API AMapGenerator : public AActor
{
#pragma region preset
	GENERATED_BODY()
public:	
	AMapGenerator();
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;
#pragma endregion
	

//Поля--------------------------------------------------------
public:
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> mPlatform;
	UPROPERTY(EditAnywhere) int mRadius = 4;

private:
	struct Platform {
		FVector2d position;
		AActor* actor;

		bool operator==(const Platform& other)
		{
			return (position == other.position) && (actor == other.actor);
		}
	};

private:	
	FVector mPlayerSpawnPos;
	FVector mPlayerPos;
	FVector mPrevPos;

	double mRadiusInUnits;
	double mPlatformSize;
	TArray<Platform> mSpawnedPlatforms;

	double mHeightLevel;
	

//Методы-----------------------------------------------------
private:
	void Init();
	void StartGenerate();
	void MapCheck();
	void UpdatePlayerPos();
	void BoundsCheck();

	FVector2d unitsPosToAbstract(FVector3d pos);
	Platform makePlatform(int x, int y);
	bool ifAlreadySpawned(FVector2d pos);

};
