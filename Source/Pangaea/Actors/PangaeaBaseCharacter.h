// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PangaeaBaseCharacter.generated.h"

class UPangaeaAnimInstance;

UCLASS(Blueprintable)
class PANGAEA_API APangaeaBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APangaeaBaseCharacter();
	
	UPROPERTY(EditAnywhere, Category="Pangaea Character Params")
	int HealthPoints = 100;
	
	UPROPERTY(EditAnywhere, Category="Pangaea Character Params")
	float Strength = 10.f;
	
	UPROPERTY(EditAnywhere, Category="Pangaea Character Params")
	float Armor = 1.f;

	UPROPERTY(EditAnywhere, Category="Pangaea Character Params")
	float AttackRange = 200.f;
	
	UPROPERTY(EditAnywhere, Category="Pangaea Character Params")
	float AttackInterval = 3.f;
	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintCallable, Category="Pangaea|Character", meta=(DisplayName="GetHP"))
	int GetHealthPoints();
	
	UFUNCTION(BlueprintCallable, Category="Pangaea|Character")
	bool IsKilled();
	
	UFUNCTION(BlueprintCallable, Category="Pangaea | PlayerCharacter")
	bool CanAttack();
	
	virtual void Attack();
	virtual void Hit(int Damage);
	virtual void DieProcess();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPangaeaAnimInstance* _AnimInstance;
	int _HealthPoints;
	float _AttackCountingDown;

};
