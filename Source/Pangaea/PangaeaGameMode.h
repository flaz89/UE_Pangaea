// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PangaeaGameMode.generated.h"

class AProjectile;
/**
 *  Simple Game Mode for a top-down perspective game
 *  Sets the default gameplay framework classes
 *  Check the Blueprint derived class for the set values
 */
UCLASS(MinimalAPI)
class APangaeaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	/** Constructor */
	APangaeaGameMode();
	~APangaeaGameMode();
	
	AProjectile* SpawnOrGetFireball(UClass* ProjectileClass);
	void RecycleFireball(AProjectile* Projectile);
	
protected:
	TQueue<AProjectile*, EQueueMode::Spsc> _FireballPool;
};



