// Fill out your copyright notice in the Description page of Project Settings.


#include "FlatSpawner.h"
#include "Components/BoxComponent.h"
#include "Flat.h"


// Sets default values
AFlatSpawner::AFlatSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	SpawnVolume->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AFlatSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}
void AFlatSpawner::SpawnActor()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	GetWorld()->SpawnActor<AFlat>(SpawnLocation, SpawnRotation);
}
// Called every frame
void AFlatSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

