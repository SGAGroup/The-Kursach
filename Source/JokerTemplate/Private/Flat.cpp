// Fill out your copyright notice in the Description page of Project Settings.


#include "Flat.h"
#include "Components/BoxComponent.h" 
#include "Components/SceneComponent.h"


// Sets default values
AFlat::AFlat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//cubeMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	///*cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;
	//cubeMeshComp->SetStaticMesh(cubeMesh);*/
	///*RootComponent = cubeMeshComp;*/
	//cubeMeshComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//cubeMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//cubeMeshComp->SetWorldScale3D(FVector(93,70,0.1));
	// Create a static mesh component
	UStaticMeshComponent* cubeMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));

	// Load the Cube mesh
	UStaticMesh* cubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Engine/BasicShapes/Cube.Cube'")).Object;

	// Set the component's mesh
	cubeMeshComponent->SetStaticMesh(cubeMesh);

	// Set as root component
	RootComponent = cubeMeshComponent;
	cubeMeshComponent->SetWorldScale3D(FVector(100, 10, 90));
}

// Called when the game starts or when spawned
void AFlat::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

