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
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> EnemyToSpawn;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> ActorToStuck;
	UPROPERTY(EditAnywhere)
	float radius = 5.f; //spawnzone
	UPROPERTY(EditAnywhere)
	float deltaTime = 10; //s
	UPROPERTY(EditAnywhere)
	int packCount = 10;


	float currentDt;

	TArray<AActor*> StillAliveChildren;

public:
	void Spawn();

	UFUNCTION(BlueprintCallable) void ExcludeChild(AActor* child);
	void SpawnOne();

	void UpdateTime(double dt);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* SpawnVolume;
};
