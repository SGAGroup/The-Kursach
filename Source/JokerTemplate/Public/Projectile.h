// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Projectile.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JOKERTEMPLATE_API UProjectile : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UProjectile();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


private:
	bool initialized = false;
	double speed = 0;
	double damage = 0;

	AActor* sourceActor;

public:
	void SetProjectile(double _speed, double _damage);
	UFUNCTION(BlueprintCallable) double GetDamage();
	UFUNCTION(BlueprintCallable) void SetSourceActor(AActor* _sourceActor);
	UFUNCTION(BlueprintCallable) AActor* GetSourceActor();


};
