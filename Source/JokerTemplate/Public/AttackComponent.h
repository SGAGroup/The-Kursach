// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

#include "AttackComponent.generated.h"




UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOKERTEMPLATE_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

/*------��������� ������-------------------------------------------------------*/
public: 
	UFUNCTION(BlueprintCallable) void checkTargets();
	UFUNCTION(BlueprintCallable) void setSphereRootComponent(USceneComponent* root);

	UFUNCTION(BlueprintCallable) void AttackTargets();

/*------��������� ����-------------------------------------------------------*/
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double widthAngle = 60; //in degrees
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double sphereRadius = 200.;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double damage = 10.;

/*------��������� ����-------------------------------------------------------*/
private:
	USphereComponent* AttackingCollision;
	TArray<TObjectPtr<AActor>> targetsToAttack;

	FVector current = FVector(0, 0, 0);

/*------��������� ��������-------------------------------------------------------*/
private:
	UFUNCTION()
	void OnOverlapBegin(
		class UPrimitiveComponent* OverlappedComp, 
		class AActor* OtherActor, 
		class UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(
		class UPrimitiveComponent* OverlappedComp,
		class AActor* OtherActor,
		class UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex);

};
