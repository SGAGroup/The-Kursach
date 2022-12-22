// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "DartProjectileAttack.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JOKERTEMPLATE_API UDartProjectileAttack : public UAttackComponent
{
	GENERATED_BODY()
		
public:
	UDartProjectileAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Методы
public:
	void PerformAttack() override;

	//Поля
public:
	UPROPERTY(EditAnywhere) TSubclassOf<AActor> projectile;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double speed = 20;

private:
	void assignSpeed(AActor* projectile);
};
