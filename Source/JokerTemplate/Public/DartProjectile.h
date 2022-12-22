// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "DartProjectile.generated.h"


UCLASS()
class JOKERTEMPLATE_API UDartProjectile : public UProjectile
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UDartProjectile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	UPROPERTY(EditAnywhere) double deltaSpeed = 0.1;
};
