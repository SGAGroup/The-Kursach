// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Spawner.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JOKERTEMPLATE_API USpawner : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpawner();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	std::list<AActor> enemies = {}; //All enemies;
	float radius = 5.f; //spawnzone

	float deltaTime = 100; //ms
	int packCount = 10;

public:
	void Spawn();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* SpawnVolume;
};
