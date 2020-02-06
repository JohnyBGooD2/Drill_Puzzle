// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DrillPuzzleGameMode.h"
#include "DrillPuzzleHUD.h"
#include "DrillPuzzleCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADrillPuzzleGameMode::ADrillPuzzleGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ADrillPuzzleHUD::StaticClass();
}
