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

	StillAliveChildren.Empty();
	Spawn();
}

void AAActorSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UE_LOG(LogTemp, Warning, TEXT("Some warning message"));
}



void AAActorSpawner::Spawn() {
	for (int i = 0; i < packCount; i++) {
		SpawnOne();
	}
}

void AAActorSpawner::SpawnOne() {
	if (EnemyToSpawn == NULL) return;

	FVector SpawnerLocation = GetActorLocation();
	FRotator SpawnerRotation = GetActorRotation();

	float randX, randY;
	randX = FMath::FRandRange(-radius, radius);
	randY = FMath::FRandRange(-radius, radius);

	FVector SpawnLocation = FVector(SpawnerLocation.X + randX, SpawnerLocation.Y + randY, SpawnerLocation.Z);
	AActor* new_enemy = GetWorld()->SpawnActor<AActor>(EnemyToSpawn, SpawnLocation, SpawnerRotation);
	new_enemy->SetOwner(this);
	StillAliveChildren.Add(new_enemy);
}

void AAActorSpawner::ExcludeChild(AActor* child) {
	StillAliveChildren.Remove(child);
	child->Destroy();
	SpawnOne();
}
