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

	//Либо равно себе, либо ограничено MAX_HEALTH
	health = FMath::Min(health, MAX_HEALTH);
	if (health < 0) SetDead(true);
}
void UHealth::ChangeHealth(int p_delta) {
	SetHealth(GetHealth() + p_delta);

	OnHealthChanged.Broadcast();
}
void UHealth::TakeDamage(int p_delta) {
	ChangeHealth(p_delta * -1);

	OnTakeDamage.Broadcast();
}
void UHealth::TakeHeal(int p_delta) {
	ChangeHealth(p_delta);

	OnTakeHeal.Broadcast();
}
void UHealth::SetDead(bool Status) {
	isDead = Status;
	if (isDead) OnDead.Broadcast();
}
bool UHealth::GetDeadStatus() {
	return isDead;
}


