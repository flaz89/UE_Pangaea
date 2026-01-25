// Fill out your copyright notice in the Description page of Project Settings.


#include "DefenseTower.h"

#include "Components/BoxComponent.h"


// Sets default values
ADefenseTower::ADefenseTower()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	_BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = _BoxComponent;
	
	_MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	_MeshComponent->SetupAttachment(_BoxComponent);
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

// Called when the game starts or when spawned
void ADefenseTower::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefenseTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

