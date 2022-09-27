// Fill out your copyright notice in the Description page of Project Settings.


#include "AActorSpawner.h"
#include "Components/BoxComponent.h"



AAActorSpawner::AAActorSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
}

void AAActorSpawner::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 10; i++) {
		Spawn();
		UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
	}
}

void AAActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));

	
}



void AAActorSpawner::Spawn() {
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();

	//GetWorld()->SpawnActor<>(SpawnLocation, SpawnRotation);
}
