// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "PlayerAvatar.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	_LifeCountingDown = Lifespan;
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (_LifeCountingDown > 0.f)
	{
		// update projectile location
		FVector CurrentLocation = GetActorLocation();
		FVector Velocity = GetActorRotation().RotateVector(FVector::ForwardVector) * Speed * DeltaTime;
		FVector NextLocation = CurrentLocation + Velocity;
		SetActorLocation(NextLocation);
		
		// perform hit detection (trace) and hit consequences
		FHitResult HitResult;
		FCollisionObjectQueryParams CollisionParams;
		CollisionParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
		
		if (GetWorld()->LineTraceSingleByObjectType(HitResult, CurrentLocation, NextLocation, CollisionParams))
		{
			APlayerAvatar* PlayerAvatar = Cast<APlayerAvatar>(HitResult.GetActor());
			if (PlayerAvatar != nullptr)
			{
				PlayerAvatar->Hit(Damage);
				PrimaryActorTick.bCanEverTick = false;
				Destroy();
			}
		}
		
		_LifeCountingDown -= DeltaTime;
	}
	else
	{
		PrimaryActorTick.bCanEverTick = false;
		Destroy();
	}
}

