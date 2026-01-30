// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyController.h"
#include "Weapon.h"
#include "AnimInstance/PangaeaAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/PawnSensingComponent.h"


// Sets default values
AEnemy::AEnemy()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensor"));
	static ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintClass(TEXT("/Game/Pangaea/Blueprints/Weapons/BP_Hammer.BP_Hammer"));
	_WeaponClass = BlueprintClass.Object->GeneratedClass;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	_Weapon = Cast<AWeapon>(GetWorld()->SpawnActor(_WeaponClass));
	_Weapon->Holder = this;
	_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_AnimInstance)
	{
		_AnimInstance->Speed= GetCharacterMovement()->Velocity.Size2D();

		if (_AttackCountingDown == AttackInterval) _AnimInstance->State = ECharacterState::Attack;
		if (_AttackCountingDown > 0.f) _AttackCountingDown -= DeltaTime;
		if (_ChasedTarget != nullptr && _AnimInstance->State == ECharacterState::Locomotion)
		{
			if (AEnemyController* EnemyAIController = Cast<AEnemyController>(GetController()))
				EnemyAIController->MakeAttackDecision(_ChasedTarget);
		} 
	}
}

void AEnemy::Attack()
{
	Super::Attack();
	
	APangaeaBaseCharacter::Attack();
	GetController()->StopMovement();
}

void AEnemy::DieProcess()
{
	Super::DieProcess();
	_Weapon->Destroy();
}

void AEnemy::Chase(APawn* TargetPawn)
{
	if (TargetPawn != nullptr  && _AnimInstance->State == ECharacterState::Locomotion)
	{
		AEnemyController* EnemyController = Cast<AEnemyController>(GetController());
		if (EnemyController) EnemyController->MoveToActor(TargetPawn, 90.f);
	}
	_ChasedTarget = TargetPawn;
}


