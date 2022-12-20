// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstAid.h"
#include "Components/BoxComponent.h"

// Sets default values
AFirstAid::AFirstAid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
}

// Called when the game starts or when spawned
void AFirstAid::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstAid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

