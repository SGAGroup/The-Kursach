// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Health.h"


UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAttackComponent::PerformAttack() {
	UE_LOG(LogTemp, Warning, TEXT("Attack!"));
}






