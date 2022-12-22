#include "Health.h"

UHealth::UHealth()
{
	PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
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
	if (health < 0) {
		health = 0;
		SetDead(true);
	}
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


