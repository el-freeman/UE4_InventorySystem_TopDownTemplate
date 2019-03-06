// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArpgGameMode.h"
#include "ArpgPlayerController.h"
#include "ArpgCharacter.h"
#include "UObject/ConstructorHelpers.h"

AArpgGameMode::AArpgGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AArpgPlayerController::StaticClass();
	DefaultPawnClass = AArpgCharacter::StaticClass();
}