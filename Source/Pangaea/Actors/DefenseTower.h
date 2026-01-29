// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DefenseTower.generated.h"

class APlayerAvatar;
class USphereComponent;

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
	
		
	FORCEINLINE USphereComponent* GetSphereComponent() const { return _SphereComponent; };
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() const { return _MeshComponent; };
	
	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
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
	TObjectPtr<USphereComponent> _SphereComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Tower Component", meta=(AllowPrivateAccess=true))
	TObjectPtr<UStaticMeshComponent> _MeshComponent;

	APlayerAvatar* _Target = nullptr;
	UClass* _Fireball;
};
