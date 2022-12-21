// Fill out your copyright notice in the Description page of Project Settings.


// Fill out your copyright notice in the Description page of Project Settings.


#include "MedBag.h"
#include "Components/BoxComponent.h"
#include "JokerTemplate/JokerTemplateCharacter.h"

// Sets default values
AMedBag::AMedBag()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	CollisionBox->SetupAttachment(GetRootComponent());
	CollisionBox->InitBoxExtent(FVector(10.f, 10.f, 10.f));
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMedBag::OnVolumeBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &AMedBag::OnVolumeEndOverlap);
}

// Called when the game starts or when spawned
void AMedBag::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMedBag::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	

}
void AMedBag::OnVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	UE_LOG(LogTemp, Warning, TEXT("OVERLAP OCCURED"));
auto Huy = Cast<AJokerTemplateCharacter>(OtherActor);
	if (Cast<AJokerTemplateCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP OCCURED"));
		Huy->StartHealing();
		Destroy();
	}
}

void AMedBag::OnVolumeEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AJokerTemplateCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("OVERLAP OCCURED"));
		
		Destroy();
	}
}