// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values for this component's properties
UProjectile::UProjectile()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProjectile::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UProjectile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!initialized) return;

	FVector newLocation = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() * speed;
	this->GetOwner()->SetActorLocation(newLocation);


	UpdateTime(DeltaTime);
}


void UProjectile::SetProjectile(double _speed, double _damage) {

	speed = _speed;
	damage = _damage;

	initialized = true;
}


double UProjectile::GetDamage() {
	return damage;
}

AActor* UProjectile::GetSourceActor() {
	return sourceActor;
}

void UProjectile::SetSourceActor(AActor* _sourceActor) {
	sourceActor = _sourceActor;
}

void UProjectile::UpdateTime(double dt)
{
	timeToLive -= dt;
	if (timeToLive < 0)
		if (GetOwner()) {
			GetOwner()->Destroy();
			DestroyComponent();
		}
}
