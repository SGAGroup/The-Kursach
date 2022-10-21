// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Flat.generated.h"

UCLASS()
class JOKERTEMPLATE_API AFlat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlat();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//	class UBoxComponent* BoxComp;
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* cubeMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMesh* cubeMesh;*/

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
