// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PangaeaBaseCharacter.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

class AWeapon;
class UPawnSensingComponent;

UCLASS()
class PANGAEA_API AEnemy : public APangaeaBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();
	virtual void Tick(float DeltaTime) override;
	
	virtual void Attack() override;
	virtual void DieProcess() override;
	
	UFUNCTION(BlueprintCallable, Category="Pangaea|Enemy")
	void Chase(APawn* TargetPawn);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	APawn* _ChasedTarget = nullptr;
	UClass* _WeaponClass;
	AWeapon* _Weapon;
	
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess=true))
	UPawnSensingComponent* _PawnSensingComponent = nullptr;
	

};
