// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseTower.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class PANGAEA_API ADefenseTower : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADefenseTower();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(EditAnywhere, Category="Tower Params")
	int HealthPoints = 100;
	
	UPROPERTY(EditAnywhere, Category="Tower Params")
	int ShellDefense = 3;
	
	UPROPERTY(EditAnywhere, Category="Tower Params")
	float AttackRange = 6.f;
	
	UPROPERTY(EditAnywhere, Category="Tower Params")
	float AttackInterval = 1.f;
	
		
	FORCEINLINE UBoxComponent* GetBoxComponent() const { return _BoxComponent; };
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return _MeshComponent; };
	
	UFUNCTION(BlueprintPure, Category="Pangaea | Defense Tower", meta=(DisplayName="GetHP"))
	int GetHealthPoints();
	
	UFUNCTION(BlueprintPure, Category="Pangaea | Defense Tower")
	bool IsDestroyed();
	
	UFUNCTION(BlueprintPure, Category="Pangaea | Defense Tower")
	bool CanFire();
	
	void Fire();
	void Hit(int Damage);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void DestructionProcess();
	
	int _HealthPoints;
	float _ReloadCountindDown;
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tower Component", meta=(AllowPrivateAccess=true))
	TObjectPtr<UBoxComponent> _BoxComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tower Component", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> _MeshComponent;

};
