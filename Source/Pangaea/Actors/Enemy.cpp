// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"

#include "EnemyController.h"
#include "Weapon.h"
#include "AnimInstance/EnemyAnimInstance.h"
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
	
	_HealthPoints = HealthPoints;
	
	_Weapon = Cast<AWeapon>(GetWorld()->SpawnActor(_WeaponClass));
	_Weapon->Holder = this;
	_Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("hand_rSocket"));
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	UEnemyAnimInstance* EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (EnemyAnimInstance)
	{
		EnemyAnimInstance->Speed= GetCharacterMovement()->Velocity.Size2D();

		if (_AttackCountingDown == AttackInterval) EnemyAnimInstance->State = EEnemyState::Attack;
		if (_AttackCountingDown > 0.f) _AttackCountingDown -= DeltaTime;
		if (_ChasedTarget != nullptr && EnemyAnimInstance->State == EEnemyState::Locomotion)
		{
			if (AEnemyController* EnemyAIController = Cast<AEnemyController>(GetController()))
				EnemyAIController->MakeAttackDecision(_ChasedTarget);
		} 
	}
}

int AEnemy::GetHealtPoint()
{
	return _HealthPoints;
}

bool AEnemy::IsKilled()
{
	return (_HealthPoints <= 0.f);
}

bool AEnemy::CanAttack()
{
	UEnemyAnimInstance* EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	return (_AttackCountingDown <= 0.f && EnemyAnimInstance->State == EEnemyState::Locomotion);
}

void AEnemy::Chase(AActor* TargetPawn)
{
	UEnemyAnimInstance* EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (TargetPawn != nullptr && EnemyAnimInstance && EnemyAnimInstance->State == EEnemyState::Locomotion)
	{
		AEnemyController* EnemyController = Cast<AEnemyController>(GetController());
		if (EnemyController) EnemyController->MoveToActor(TargetPawn, 90.f);
	}
	_ChasedTarget = TargetPawn;
}

void AEnemy::Attack()
{
	GetController()->StopMovement();
	_AttackCountingDown = AttackInterval;
}

void AEnemy::Hit(int Damage)
{
	_HealthPoints -= Damage;
	UEnemyAnimInstance* EnemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (EnemyAnimInstance) EnemyAnimInstance->State = EEnemyState::Hit;
	
	if (IsKilled()) DieProcess();
}

void AEnemy::DieProcess()
{
	PrimaryActorTick.bCanEverTick = false;
	K2_DestroyActor();
	Destroy();
	GEngine->ForceGarbageCollection(true);
}

