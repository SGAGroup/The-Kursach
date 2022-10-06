// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Health.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class JOKERTEMPLATE_API UHealth : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealth();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	//^^^^^^^^^^^^^^^^^^^^^^^^
	//��� ��� �� ������



	//��� �Ψ
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int health = 100; //������� ��������
	UPROPERTY(EditAnywhere)
		int MAX_HEALTH = 100; //������������ ��������
	bool isDead = false; //���� �� ��
public:
	UFUNCTION(BlueprintPure) int GetHealth(); //���������� ������� ��������
	UFUNCTION(BlueprintPure) int GetMaxHealth(); //���������� ������������ ��������

	UFUNCTION(BlueprintCallable) void SetHealth(int NewHealth); //������������� �������� ��������
	UFUNCTION(BlueprintCallable) void ChangeHealth(int p_delta); //������ ��������
	UFUNCTION(BlueprintCallable) void TakeDamage(int Damage); //������ ��������(��������� �����)
	UFUNCTION(BlueprintCallable) void TakeHeal(int Heal); //������ ��������(��������������)
	UFUNCTION(BlueprintCallable) void SetDead(bool Status); //������������� ���� ������
	UFUNCTION(BlueprintCallable) bool GetDeadStatus(); //�������� ���������� �������(���, �����)
};

/*
float ratio = 0.23; //23%

//Green
int colors[] = { 0, 0.2, 0.4, 0.6, 0.8, 1 };

int main() {
	if (ratio < 0.2) std::cout << "1";
	else if (ratio < 0.4) std::cout << "2";
	else if (ratio < 0.4) std::cout << "2";
	else if (ratio < 0.4) std::cout << "2";
	else if (ratio < 0.4) std::cout << "2";
}
*/