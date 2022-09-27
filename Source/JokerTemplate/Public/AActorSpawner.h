// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AActorSpawner.generated.h"

UCLASS()
class JOKERTEMPLATE_API AAActorSpawner : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AAActorSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;






public:
	std::list<AActor*> enemies = {}; //All enemies;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AActor* enemy;
	float radius = 5.f; //spawnzone

	float deltaTime = 100; //ms
	int packCount = 10;

public:
	void Spawn();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* SpawnVolume;
};
