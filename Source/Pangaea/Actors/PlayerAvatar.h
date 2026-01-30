// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PangaeaBaseCharacter.h"
#include "PangaeaCharacter.h"
#include "GameFramework/Character.h"
#include "PlayerAvatar.generated.h"

class AWeapon;
class UCameraComponent;
class USpringArmComponent;

UCLASS(Blueprintable)
class PANGAEA_API APlayerAvatar : public APangaeaBaseCharacter
{
	GENERATED_BODY()

public:
	APlayerAvatar();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	TObjectPtr<UCameraComponent> GetCameraComponent() const { return _CameraComponent; }
	TObjectPtr<USpringArmComponent> GetSpringArmComponent() const { return _SpringArmComponent; }
	
	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatr")
	void AttachWeapon(AWeapon* Weapon);
	UFUNCTION(BlueprintCallable, Category = "Pangaea|PlayerAvatr")
	void DropWeapon();
	
	virtual void Attack() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess=true))
	TObjectPtr<USpringArmComponent> _SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta=(AllowPrivateAccess=true))
	TObjectPtr<UCameraComponent> _CameraComponent;

};
