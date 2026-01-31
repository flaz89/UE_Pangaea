// Copyright Epic Games, Inc. All Rights Reserved.

#include "PangaeaGameMode.h"

#include "PangaeaPlayerController.h"
#include "Actors/Projectile.h"

APangaeaGameMode::APangaeaGameMode()
{
	PlayerControllerClass = APangaeaPlayerController::StaticClass();
	
}

APangaeaGameMode::~APangaeaGameMode()
{
	AProjectile* Fireball;
	while (!_FireballPool.IsEmpty() && _FireballPool.Dequeue(Fireball))
	{
		Fireball->Destroy();
	}
	_FireballPool.Empty();
}

AProjectile* APangaeaGameMode::SpawnOrGetFireball(UClass* ProjectileClass)
{
	AProjectile* Fireball = nullptr;
	if (_FireballPool.IsEmpty())
	{
		Fireball = Cast<AProjectile>(GetWorld()->SpawnActor(ProjectileClass));
	}
	else
	{
		_FireballPool.Dequeue(Fireball);
		Fireball->Reset();
	}
	return Fireball;
}

void APangaeaGameMode::RecycleFireball(AProjectile* Projectile)
{
	if (Projectile == nullptr) return;
	
	Projectile->SetActorHiddenInGame(true);
	Projectile->SetActorEnableCollision(false);
	Projectile->SetActorTickEnabled(false);
	_FireballPool.Enqueue(Projectile);
}
