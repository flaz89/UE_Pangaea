// Fill out your copyright notice in the Description page of Project Settings.


#include "PangaeaBaseCharacter.h"

#include "AnimInstance/PangaeaAnimInstance.h"


// Sets default values
APangaeaBaseCharacter::APangaeaBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APangaeaBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	_AnimInstance = Cast<UPangaeaAnimInstance>(GetMesh()->GetAnimInstance());
	_HealthPoints = HealthPoints;
}

// Called every frame
void APangaeaBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APangaeaBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

int APangaeaBaseCharacter::GetHealthPoints()
{
	return _HealthPoints = HealthPoints;
}

bool APangaeaBaseCharacter::IsKilled()
{
	return (_HealthPoints > 0.f);
}

bool APangaeaBaseCharacter::CanAttack()
{
	return (_AttackCountingDown <= 0.f && _AnimInstance->State==ECharacterState::Locomotion);
}

void APangaeaBaseCharacter::Attack()
{
	_AttackCountingDown = AttackInterval;
}

void APangaeaBaseCharacter::Hit(int Damage)
{
	_HealthPoints -= Damage;
	_AnimInstance->State = ECharacterState::Hit;
	
	if (IsKilled()) PrimaryActorTick.bCanEverTick = false;
}

void APangaeaBaseCharacter::DieProcess()
{
	PrimaryActorTick.bCanEverTick = false;
	Destroy();
	GEngine->ForceGarbageCollection();
}

