// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PrimitiveComponent.h"
#include "Components/SphereComponent.h"

#include "PrimitiveAttackComponent.generated.h"


UCLASS()
class JOKERTEMPLATE_API UPrimitiveAttackComponent : public UPrimitiveComponent
{
	GENERATED_BODY()

public:
	UPrimitiveAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

/*------œ”¡À»◊Õ€≈ Ã≈“Œƒ€-------------------------------------------------------*/
public:
	UFUNCTION(BlueprintCallable) void checkTargets();
	UFUNCTION(BlueprintCallable) void setSphereRootComponent(USceneComponent* root);


/*------œ”¡À»◊Õ€≈ œŒÀﬂ-------------------------------------------------------*/
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double widthAngle = 60; //in degrees
	UPROPERTY(EditAnywhere, BlueprintReadWrite) double sphereRadius = 100.;

/*------œ–»¬¿“Õ€≈ œŒÀﬂ-------------------------------------------------------*/
private:
	USphereComponent* AttackingCollision;
	TArray<TObjectPtr<AActor>> targetsToAttack;

/*------œ–»¬¿“Õ€≈ ƒÂÎÂ„‡Ú˚-------------------------------------------------------*/
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
