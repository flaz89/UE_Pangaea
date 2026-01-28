// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAvatar.h"

#include "AnimInstance/PlayerAvatarAnimInstance.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"


// Sets default values
APlayerAvatar::APlayerAvatar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
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
	
	// avoiding character rotate with player controller
	bUseControllerRotationRoll = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	
	UCharacterMovementComponent* CharacterMovemenetComponent = GetCharacterMovement();
	CharacterMovemenetComponent->bOrientRotationToMovement = true;
	CharacterMovemenetComponent->RotationRate = FRotator(0.0f, 640.0f, 0.0f);
	CharacterMovemenetComponent->bConstrainToPlane = true;
	CharacterMovemenetComponent->bSnapToPlaneAtStart = true;
}

int APlayerAvatar::GetHealthPoints()
{
	return _HealthPoints;
}

bool APlayerAvatar::IsKilled()
{
	return (_HealthPoints <= 0.f);
}

bool APlayerAvatar::CanAttack()
{
	// retrive player character and set CanAttack() return "true"
	// if count down ins <= 0 and player state is != Attack (but only if is == to Locomotion state)
	UPlayerAvatarAnimInstance* PlayerAnimInstance = Cast<UPlayerAvatarAnimInstance>(GetMesh()->GetAnimInstance());
	return (_AttackCountingDown <= 0.f && PlayerAnimInstance->PlayerState == EPlayerState::Locomotion);
}

void APlayerAvatar::Attack()
{
	_AttackCountingDown = AttackInterval;
}

// Called when the game starts or when spawned
void APlayerAvatar::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerAvatar::DieProcess()
{
	// forcing GC to dellocate memory, but can be simply done with Destroy() letting the reflection system do it for us
	PrimaryActorTick.bCanEverTick = false;
	Destroy();
	GEngine->ForceGarbageCollection( true );
}

// Called every frame
void APlayerAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// update Speed value from PlayerAnimInstance
	UPlayerAvatarAnimInstance* AnimInstancePlayerAvatar = Cast<UPlayerAvatarAnimInstance>(GetMesh()->GetAnimInstance());
	AnimInstancePlayerAvatar->Speed = GetCharacterMovement()->Velocity.Size2D();
	
	if (_AttackCountingDown == AttackInterval) AnimInstancePlayerAvatar->PlayerState = EPlayerState::Attack;
	if (_AttackCountingDown > 0.f) _AttackCountingDown -= DeltaTime;
}

// Called to bind functionality to input
void APlayerAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

