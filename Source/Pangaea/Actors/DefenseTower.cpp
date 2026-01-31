// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseTower.h"

#include "PangaeaCharacter.h"
#include "PangaeaGameMode.h"
#include "PlayerAvatar.h"
#include "Projectile.h"
#include "Weapon.h"
#include "AnimInstance/PangaeaAnimInstance.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADefenseTower::ADefenseTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Box Collision"));
	RootComponent = _SphereComponent;
	_SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ADefenseTower::OnSphereBeginOverlap);
	_SphereComponent->OnComponentEndOverlap.AddDynamic(this, &ADefenseTower::OnSphereEndOverlap);
	
	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_MeshComponent->SetupAttachment(_SphereComponent);
	
	static ConstructorHelpers::FObjectFinder<UBlueprint> BlueprintClass(TEXT("/Game/Pangaea/Blueprints/Weapons/BP_Projectile.BP_Projectile"));
	_Fireball = BlueprintClass.Object->GeneratedClass;
}

void ADefenseTower::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerAvatar* Player = Cast<APlayerAvatar>(OtherActor);
	if (Player) _Target = Player;
}

void ADefenseTower::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APlayerAvatar* Player = Cast<APlayerAvatar>(OtherActor);
	if (_Target != nullptr && OtherActor == _Target) _Target = nullptr;
}

void ADefenseTower::OnMeshBeginOverlap(AActor* OtherActor)
{
	AWeapon* Weapon = Cast<AWeapon>(OtherActor);
	if (Weapon == nullptr || Weapon->Holder == nullptr) return;
	
	APlayerAvatar* WeaponOwner = Cast<APlayerAvatar>(Weapon->Holder);
	if (WeaponOwner == nullptr) return;
	
	UPangaeaAnimInstance* AnimInstance = Cast<UPangaeaAnimInstance>(WeaponOwner->GetMesh()->GetAnimInstance());
	if (AnimInstance->State == ECharacterState::Attack  && CanBeDamaged())
	{
		Hit(WeaponOwner->Strength);
	}
}

void ADefenseTower::Hit(int Damage)
{
}

int ADefenseTower::GetHealthPoints()
{
	return _HealthPoints;
}

bool ADefenseTower::IsDestroyed()
{
	return (_HealthPoints > 0.f);
}

bool ADefenseTower::CanFire()
{
	return (_ReloadCountindDown <= 0.f);
}

void ADefenseTower::Fire()
{
	/*if (!HasAuthority()) return;
	if (_PangaeaGameMode == nullptr) return;*/
	
	AProjectile* Fireball = _PangaeaGameMode->SpawnOrGetFireball(_Fireball);
	
	FVector StartLocation = GetActorLocation();
	StartLocation.Z += 100.0f;
	FVector TargetLocation = _Target->GetActorLocation();
	TargetLocation.Z = StartLocation.Z;
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(StartLocation, TargetLocation);
	
	Fireball->SetActorLocation(StartLocation);
	Fireball->SetActorRotation(Rotation);
	
	/*FActorSpawnParameters SpawnParams;
	AProjectile* Fireball = GetWorld()->SpawnActor<AProjectile>(_Fireball, StartLocation, Rotation, SpawnParams);*/
	
}	

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorTickInterval(0.5f);
	/*if (!HasAuthority())*/ 
	_PangaeaGameMode = Cast<APangaeaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_Target != nullptr) Fire();
}

