// Copyright Epic Games, Inc. All Rights Reserved.

#include "PangaeaGameMode.h"

#include "PangaeaPlayerController.h"

APangaeaGameMode::APangaeaGameMode()
{
	// stub
	PlayerControllerClass = APangaeaPlayerController::StaticClass();
}
