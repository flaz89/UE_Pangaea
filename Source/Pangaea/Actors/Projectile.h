// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TwinStickProjectile.h"
#include "Projectile.generated.h"

class APangaeaGameMode;

UCLASS(Blueprintable)
class PANGAEA_API AProjectile : public ATwinStickProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectile();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category="Projectile Params")
	float Speed = 800.f;
	
	UPROPERTY(EditAnywhere, Category="Projectile Params")
	float Lifespan = 5.f;
	
	UPROPERTY(EditAnywhere, Category="Projectile Params")
	float Damage = 10.f;

	void Reset();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	float _LifeCountingDown;
	
	APangaeaGameMode* _PangaeaGameMode;
	
	
};
