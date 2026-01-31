// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "PangaeaGameMode.h"
#include "PlayerAvatar.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AProjectile::Reset()
{
	_LifeCountingDown = Lifespan;
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
	SetActorTickEnabled(true);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
    
	//_LifeCountingDown = Lifespan;
	_PangaeaGameMode = Cast<APangaeaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	
	UProjectileMovementComponent* ProjMovement = FindComponentByClass<UProjectileMovementComponent>();
	if (ProjMovement)
	{
		ProjMovement->Deactivate();
	}
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
				//Destroy();
				_PangaeaGameMode->RecycleFireball(this);
			}
		}
		_LifeCountingDown -= DeltaTime;
	}
	else
	{
		//Destroy();
		_PangaeaGameMode->RecycleFireball(this);
	}
}

