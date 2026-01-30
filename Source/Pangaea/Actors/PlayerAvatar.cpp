// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"

#include "Weapon.h"
#include "AnimInstance/PangaeaAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APlayerAvatar::APlayerAvatar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// avoiding character rotate with player controller
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	
	UCharacterMovementComponent* CharacterMovemenet = GetCharacterMovement();
	CharacterMovemenet->bOrientRotationToMovement = true;
	CharacterMovemenet->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	CharacterMovemenet->bConstrainToPlane = true;
	CharacterMovemenet->bSnapToPlaneAtStart = true;
	
	// create the camera spring arm
	_SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	_SpringArmComponent->SetupAttachment(RootComponent);
	_SpringArmComponent->SetUsingAbsoluteRotation(true);
	_SpringArmComponent->TargetArmLength = 800.f;
	_SpringArmComponent->SetRelativeRotation(FRotator(-60.0f, 0.0f, 0.0f));
	_SpringArmComponent->bDoCollisionTest = false;
	
	// create the camera
	_CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	_CameraComponent->SetupAttachment(_SpringArmComponent, USpringArmComponent::SocketName);
	_CameraComponent->bUsePawnControlRotation = false;
}

void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// update Speed value from PlayerAnimInstance
	_AnimInstance->Speed = GetCharacterMovement()->Velocity.Size2D();
	
	if (_AttackCountingDown == AttackInterval) _AnimInstance->State = ECharacterState::Attack;
	if (_AttackCountingDown > 0.f) _AttackCountingDown -= DeltaTime;
}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void APlayerAvatar::AttachWeapon(AWeapon* Weapon)
{
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
}

void APlayerAvatar::DropWeapon()
{
	TArray<AActor*> AttachedActors;
	GetAttachedActors(AttachedActors, true);
	for (int i = 0; i < AttachedActors.Num(); i++)
	{
		AttachedActors[i]->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		AttachedActors[i]->SetActorRotation(FQuat::Identity);
		AWeapon* Weapon = Cast<AWeapon>(AttachedActors[i]);
		if (Weapon != nullptr) Weapon->Holder = nullptr;
	}
}

void APlayerAvatar::Attack()
{
	Super::Attack();
}

