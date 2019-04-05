// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ArpgGameMode.h"
#include "ArpgPlayerController.h"
#include "ArpgCharacter.h"
#include "ArpgGameState.h"
#include "UObject/ConstructorHelpers.h"

AArpgGameMode::AArpgGameMode()
{
	 //use our custom BP_PlayerController class
	static ConstructorHelpers::FClassFinder<APlayerController> ArpgPlayerControllerClass(TEXT("/Game/TopDownCPP/Blueprints/BP_ArpgPlayerController.BP_ArpgPlayerController_C"));
	if (ArpgPlayerControllerClass.Succeeded())
	{
		PlayerControllerClass = ArpgPlayerControllerClass.Class;
	}

	// if you want to use native c++ playercontroller class
	//PlayerControllerClass = AArpgPlayerController::StaticClass();
	DefaultPawnClass = AArpgCharacter::StaticClass();
	GameStateClass = AArpgGameState::StaticClass();
}