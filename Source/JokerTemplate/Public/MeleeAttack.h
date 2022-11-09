// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "Components/SphereComponent.h"
#include "MeleeAttack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JOKERTEMPLATE_API UMeleeAttack : public UAttackComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMeleeAttack();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

/*------��������� ������-------------------------------------------------------*/
public:
	UFUNCTION(BlueprintCallable) void checkTargets();
	void PerformAttack() override;


/*------��������� ������-------------------------------------------------------*/
private:
	bool isInCone(AActor* actorToCheck);

/*------��������� ����-------------------------------------------------------*/
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double widthAngle = 60; //in degrees
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double sphereRadius = 200.;

/*------��������� ����-------------------------------------------------------*/
private:
	USphereComponent* AttackingCollision;

	TSet<AActor*> targetsToAttack;

};
