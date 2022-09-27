// Fill out your copyright notice in the Description page of Project Settings.

#include "Spawner.h"
#include "Components/BoxComponent.h"

USpawner::USpawner()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void USpawner::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USpawner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// ...
}


void USpawner::Spawn() {
	
}