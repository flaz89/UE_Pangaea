// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class PANGAEA_API AWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ACharacter* Holder = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Weapon Params")
	float Strenghth = 10.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool IsWithinAttackRange(float AttackRange, AActor* Target);
	
	UPROPERTY(EditAnywhere, Category="Weapon")
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
	UFUNCTION()
	void OnWeaponBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

};
