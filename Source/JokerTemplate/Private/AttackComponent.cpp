// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Health.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AttackingCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Attacking Collision"));
	AttackingCollision->InitSphereRadius(sphereRadius);
	AttackingCollision->SetSphereRadius(sphereRadius);
	AttackingCollision->SetGenerateOverlapEvents(true);
	AttackingCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	AttackingCollision->SetHiddenInGame(false);
	AttackingCollision->SetActive(true);

	


	//AttackingCollision->SetCollisionProfileName("Trigger");

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/RED_DEBUG_MAT"));

	if (FoundMaterial.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("[UAttackComponent] Material was found"));
		AttackingCollision->SetMaterialByName(TEXT("RED_DEBUG_MAT"), FoundMaterial.Object);
	}
	
	//AttackingCollision->OnComponentBeginOverlap.AddDynamic(this, &UAttackComponent::OnOverlapBegin);
	//AttackingCollision->OnComponentEndOverlap.AddDynamic(this, &UAttackComponent::OnOverlapEnd);

}

// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	AttackingCollision->InitSphereRadius(sphereRadius);
	AttackingCollision->SetSphereRadius(sphereRadius);
	
}

// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	/*
	if(this->GetOwner() != NULL)
	DrawDebugSphere(GetWorld(), this->GetOwner()->GetActorLocation(), sphereRadius, 20, FColor::Cyan);
	*/

	FVector ownerPos = this->GetOwner()->GetActorLocation();
	AttackingCollision->SetWorldLocation(ownerPos);
	AttackingCollision->GetOverlappingActors(targetsToAttack);

	//DrawDebugLine(GetWorld(), ownerPos, ownerPos + this->GetOwner()->GetActorForwardVector()*100, FColor::Emerald, true, -1, 0, 2);

	for (auto target : targetsToAttack) {
		if (target == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("[Tick] target = nullptr"));
			continue;
		}

		if (target == this->GetOwner()) continue;
		if (!isInCone(target)) {
			targetsToAttack.Remove(target);
			continue;
		}
		FVector origin, extend;
		target->GetActorBounds(true, origin, extend, false);
		float width = extend.Length()/1.5;

		DrawDebugSphere(GetWorld(), target->GetActorLocation(), width, 20, FColor::Cyan);

	}

}

void UAttackComponent::AttackTargets() {
	
	for (auto target : targetsToAttack) {

		if (target == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("[Tick] target = nullptr"));
			continue;
		}

		//Attack everyone except us
		if (target == this->GetOwner()) continue;

		//Tries to get health component from each target
		UHealth* healthComponent = target->FindComponentByClass<UHealth>();
		if (healthComponent != nullptr) { //if health component exists
			healthComponent->TakeDamage(damage); //Apply damage
		}
	}

}



void UAttackComponent::checkTargets() {
	auto num = targetsToAttack.Num();
	UE_LOG(LogTemp, Warning, TEXT("Active actors count: %d"), num);

	size_t i = 0;
	for (auto target : targetsToAttack) {
		if (target == nullptr) {
			UE_LOG(LogTemp, Warning, TEXT("[Tick] target = nullptr"));
			continue;
		}

		FString str = target->GetName();
		UE_LOG(LogTemp, Warning, TEXT("Actor[%d]: %s"), i, *str)
		i++;
	}
}

void UAttackComponent::setSphereRootComponent(USceneComponent* root) {
	if (root != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Try to assign sphere root. Root: %s"), *root->GetName());
		AttackingCollision->SetupAttachment(root);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[UAttackComponent] sphereRootComponent = nullptr"));
	}
}

void UAttackComponent::OnOverlapBegin(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (OtherActor == this->GetOwner()) return;

	if (!isInCone(OtherActor)) return;

	UE_LOG(LogTemp, Warning, TEXT("Begin overlap with: %s"), *OtherActor->GetName());
	targetsToAttack.Add(OtherActor);
}


void UAttackComponent::OnOverlapEnd(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex) 
{
	if (OtherActor == this->GetOwner()) return;

	UE_LOG(LogTemp, Warning, TEXT("End overlap with: %s"), *OtherActor->GetName());
	targetsToAttack.Remove(OtherActor);
}


bool UAttackComponent::isInCone(AActor* actorToCheck) {
	
	FVector forward = this->GetOwner()->GetActorForwardVector();
	FVector toOther = actorToCheck->GetActorLocation() - this->GetOwner()->GetActorLocation();

	forward.Normalize(); toOther.Normalize();

	double dotProduct = forward.Dot(toOther);


	//double alpha = FMath::Acos(dotProduct) * 180 / PI;

	return (dotProduct >= FMath::Cos(widthAngle*PI/180));
}