// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileAttack.h"
#include "Projectile.h"



UProjectileAttack::UProjectileAttack()
{
	PrimaryComponentTick.bCanEverTick = true;

}

// Called when the game starts
void UProjectileAttack::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UProjectileAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UProjectileAttack::PerformAttack() {
	if (projectile.GetDefaultObject() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[ProjectileAttack] GetDefaultObject nullptr"));
		return;
	}

	FVector location = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() * 100;
	FRotator rotation = this->GetOwner()->GetActorRotation();

	AActor* spawned = GetWorld()->SpawnActor<AActor>(projectile, location, rotation);

	if (spawned == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[ProjectileAttack] projectile destroyed on spawn"));
		return;
	}

	UProjectile* projComponent = spawned->FindComponentByClass<UProjectile>();
	
	if (projComponent == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("[ProjectileAttack] projectile doesn't have autoMove. Can't attack"));
		return;
	}

	projComponent->SetProjectile(speed, damage);
	projComponent->SetSourceActor(this->GetOwner());
}
