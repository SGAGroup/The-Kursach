// Fill out your copyright notice in the Description page of Project Settings.


#include "DartProjectileAttack.h"
#include "Projectile.h"

template<class T>
bool checkIfNull(T* actor)
{
	if (!actor) {
		UE_LOG(LogTemp, Warning, TEXT("[ProjectileAttack] projectile destroyed on spawn"));
		return true;
	}
	return false;
}

UDartProjectileAttack::UDartProjectileAttack()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UDartProjectileAttack::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UDartProjectileAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDartProjectileAttack::PerformAttack() {
	if (projectile.GetDefaultObject() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[ProjectileAttack] GetDefaultObject nullptr"));
		return;
	}

	FVector location = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() * 30;
	FRotator rotation = this->GetOwner()->GetActorRotation();

	double yaw = 10;
	AActor* spawned = nullptr;
	for (size_t i = 0; i < 3; ++i)
	{
		FRotator additionalRotation = FRotator(0, yaw*(i+1), 0);
		spawned = GetWorld()->SpawnActor<AActor>(projectile, location, rotation + additionalRotation);
		if(spawned)
			assignSpeed(spawned);
		
		spawned = GetWorld()->SpawnActor<AActor>(projectile, location, rotation - additionalRotation);
		if(spawned)
			assignSpeed(spawned);
	}
	
}

void UDartProjectileAttack::assignSpeed(AActor* _projectile) {
	if (checkIfNull(_projectile)) return;

	UProjectile* projComponent = _projectile->FindComponentByClass<UProjectile>();

	if (projComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[ProjectileAttack] projectile doesn't have autoMove. Can't attack"));
		return;
	}

	projComponent->SetProjectile(speed, damage);
	projComponent->SetSourceActor(this->GetOwner());
}