// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class UPawnSensingComponent;

UCLASS()
class PANGAEA_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category="Enemy Params")
	int HealthPoints = 100;
	
	UPROPERTY(EditAnywhere, Category="Enemy Params")
	float Strength = 5.f;
	
	UPROPERTY(EditAnywhere, Category="Enemy Params")
	float Armor = 1.f;
	
	UPROPERTY(EditAnywhere, Category="Enemy Params")
	float AttackRange = 200.f;
	
	UPROPERTY(EditAnywhere, Category="Enemy Params")
	float AttackInterval = 3.f;
	
	UFUNCTION(BlueprintCallable, Category="Pangaea|Enemy", meta=(DisplayName="Get HP"))
	int GetHealtPoint();
	
	UFUNCTION(BlueprintCallable, Category="Pangaea|Enemy")
	bool IsKilled();
	
	UFUNCTION(BlueprintCallable, Category="Pangaea|Enemy")
	bool CanAttack();
	
	UFUNCTION(BlueprintCallable, Category="Pangaea|Enemy")
	void Chase(AActor* TargetPawn);
	
	void Attack();
	void Hit(int Damage);
	void DieProcess();
	bool IsAttacking();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int _HealthPoints;
	float _AttackCountingDown;
	AActor* _ChasedTarget = nullptr;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UPawnSensingComponent* _PawnSensingComponent = nullptr;
	

};
