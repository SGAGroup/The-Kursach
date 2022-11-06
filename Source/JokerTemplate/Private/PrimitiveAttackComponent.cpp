// Fill out your copyright notice in the Description page of Project Settings.


#include "PrimitiveAttackComponent.h"

// Sets default values for this component's properties
UPrimitiveAttackComponent::UPrimitiveAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	AttackingCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Attacking Collision"));
	AttackingCollision->InitSphereRadius(sphereRadius);


	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/RED_DEBUG_MAT"));

	if (FoundMaterial.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("[UPrimitiveComponent] Material was found"));
		AttackingCollision->SetMaterialByName(TEXT("RED_DEBUG_MAT"), FoundMaterial.Object);
	}

	AttackingCollision->OnComponentBeginOverlap.AddDynamic(this, &UPrimitiveAttackComponent::OnOverlapBegin);
	AttackingCollision->OnComponentEndOverlap.AddDynamic(this, &UPrimitiveAttackComponent::OnOverlapEnd);
}

// Called when the game starts
void UPrimitiveAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UPrimitiveAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (this->GetOwner() != NULL)
		DrawDebugSphere(GetWorld(), this->GetOwner()->GetActorLocation(), sphereRadius, 20, FColor::Cyan);
	// ...
}

void UPrimitiveAttackComponent::checkTargets() {
	auto num = targetsToAttack.Num();
	UE_LOG(LogTemp, Warning, TEXT("Active actors count: %d"), num);


	for (size_t i = 0; i < num; ++i) {
		auto target = targetsToAttack[i];
		if (!target.IsNull()) {
			FString str = target.Get()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("Actor[%d]: %s"), i, *str);
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("ALERT!!!! Pointer is NULL"));
		}
	}
}

void UPrimitiveAttackComponent::setSphereRootComponent(USceneComponent* root) {
	if (root != nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Try to assign sphere root. Root: %s"), *root->GetName());
		AttackingCollision->SetupAttachment(root);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[UPrimitiveComponent] sphereRootComponent = nullptr"));
	}
}

void UPrimitiveAttackComponent::OnOverlapBegin(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin overlap with: %s"), *OtherActor->GetName());
	targetsToAttack.Add(OtherActor);
}


void UPrimitiveAttackComponent::OnOverlapEnd(
	class UPrimitiveComponent* OverlappedComp,
	class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("End overlap with: %s"), *OtherActor->GetName());
	targetsToAttack.Remove(OtherActor);
}