// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}
// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...

}
// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


int UHealth::GetHealth() {
	return health;
}
int UHealth::GetMaxHealth() {
	return MAX_HEALTH;
}
void UHealth::SetHealth(int p_value) {
	health = p_value;
}
void UHealth::ChangeHealth(int p_delta) {
	SetHealth(GetHealth() + p_delta);
}
void UHealth::TakeDamage(int p_delta) {
	ChangeHealth(p_delta * -1);
}
void UHealth::TakeHeal(int p_delta) {
	ChangeHealth(p_delta);
}
void UHealth::SetDead(bool Status) {
	isDead = Status;
}
bool UHealth::GetDeadStatus() {
	return isDead;
}


