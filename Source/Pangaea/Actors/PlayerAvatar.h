// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerAvatar.generated.h"

UCLASS(Blueprintable)
class PANGAEA_API APlayerAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerAvatar();
	
	UPROPERTY(EditAnywhere, Category="PlayerAvatar Params")
	int HealthPoints = 500;
	
	UPROPERTY(EditAnywhere, Category="PlayerAvatar Params")
	float Strength = 10.f;
	
	UPROPERTY(EditAnywhere, Category="PlayerAvatar Params")
	float Armor = 3.f;
	
	UPROPERTY(EditAnywhere, Category="PlayerAvatar Params")
	float AttackRange = 6.f;
	
	UPROPERTY(EditAnywhere, Category="PlayerAvatar Params")
	float AttackInterval = 1.2f;
	
	UFUNCTION(BlueprintCallable, Category="Pangaea | PlayerCharacter", meta=(DisplayName="GetHP"))
	int GetHealthPoints();
	
	UFUNCTION(BlueprintCallable, Category="Pangaea | PlayerCharacter")
	bool IsKilled();
	
	UFUNCTION(BlueprintCallable, Category="Pangaea | PlayerCharacter")
	bool CanAttack();
	
	void Attack();
	bool IsAttaccking();
	void Hit(int Damage);
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int _HealthPoints;
	float _AttackCountingDown;
	
	void DieProcess();
	

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
