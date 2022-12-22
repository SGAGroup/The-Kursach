#include "DartProjectile.h"


UDartProjectile::UDartProjectile()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UDartProjectile::BeginPlay()
{
	Super::BeginPlay();

}


void UDartProjectile::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!initialized) return;

	FVector newLocation = this->GetOwner()->GetActorLocation() + this->GetOwner()->GetActorForwardVector() * speed;
	this->GetOwner()->SetActorLocation(newLocation);

	speed -= deltaSpeed;
}