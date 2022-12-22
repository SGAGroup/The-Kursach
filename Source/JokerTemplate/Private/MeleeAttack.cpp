#include "MeleeAttack.h"
#include "Health.h"

#define DRAW_DEBUG
#undef DRAW_DEBUG

// Sets default values for this component's properties
UMeleeAttack::UMeleeAttack()
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

	static ConstructorHelpers::FObjectFinder<UMaterial> FoundMaterial(TEXT("/Game/Materials/RED_DEBUG_MAT"));

	if (FoundMaterial.Succeeded()) {
		UE_LOG(LogTemp, Warning, TEXT("[UMeleeAttack] Material was found"));
		AttackingCollision->SetMaterialByName(TEXT("RED_DEBUG_MAT"), FoundMaterial.Object);
	}
	//AttackingCollision->OnComponentBeginOverlap.AddDynamic(this, &UMeleeAttack::OnOverlapBegin);
	//AttackingCollision->OnComponentEndOverlap.AddDynamic(this, &UMeleeAttack::OnOverlapEnd);
}

// Called when the game starts
void UMeleeAttack::BeginPlay()
{
	Super::BeginPlay();
	AttackingCollision->InitSphereRadius(sphereRadius);
	AttackingCollision->SetSphereRadius(sphereRadius);
	AttackingCollision->AttachToComponent(
		GetOwner()->GetRootComponent(), 
		FAttachmentTransformRules::KeepRelativeTransform);
}

// Called every frame
void UMeleeAttack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	AttackingCollision->GetOverlappingActors(targetsToAttack);

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
		float width = extend.Length() / 1.5;

		#ifdef DRAW_DEBUG 
			DrawDebugSphere(GetWorld(), target->GetActorLocation(), width, 20, FColor::Cyan);
		#endif
	}
}

void UMeleeAttack::PerformAttack() 
{
	Super::PerformAttack();
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



void UMeleeAttack::checkTargets() {
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

bool UMeleeAttack::isInCone(AActor* actorToCheck) {
	FVector forward = this->GetOwner()->GetActorForwardVector();
	FVector toOther = actorToCheck->GetActorLocation() - this->GetOwner()->GetActorLocation();
	forward.Normalize(); toOther.Normalize();
	double dotProduct = forward.Dot(toOther);

	return (dotProduct >= FMath::Cos(widthAngle * PI / 180));
}