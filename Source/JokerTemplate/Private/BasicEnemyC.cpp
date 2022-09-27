// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicEnemyC.h"

// Sets default values
ABasicEnemyC::ABasicEnemyC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;




}

// Called when the game starts or when spawned
void ABasicEnemyC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicEnemyC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

