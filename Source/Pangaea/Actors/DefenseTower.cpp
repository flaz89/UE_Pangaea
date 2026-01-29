// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseTower.h"

#include "PlayerAvatar.h"
#include "Projectile.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
ADefenseTower::ADefenseTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Box Collision"));
	RootComponent = _SphereComponent;
	
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
	if (_Target == nullptr) return;
	

	AProjectile* Fireball = Cast<AProjectile>(GetWorld()->SpawnActor(_Fireball));
	FVector FireballStartLocation = GetActorLocation();
	FireballStartLocation.Z += 100.f;
	FVector FireballEndLocation =_Target->GetActorLocation();
	FireballEndLocation.Z = FireballStartLocation.Z;
	FRotator Rotation = UKismetMathLibrary::FindLookAtRotation(FireballStartLocation, FireballEndLocation);
	Fireball->SetActorLocation(FireballStartLocation);
	Fireball->SetActorRotation(Rotation);
}

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	GetSphereComponent()->OnComponentBeginOverlap.AddDynamic(this, &ADefenseTower::OnSphereBeginOverlap);
	GetSphereComponent()->OnComponentEndOverlap.AddDynamic(this, &ADefenseTower::OnSphereEndOverlap);
	
	SetActorTickInterval(0.5f);
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_Target != nullptr) Fire();
}

