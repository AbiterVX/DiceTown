// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "DiceTownGameMode.h"
#include "DiceTownPlayerController.h"
#include "DiceTownCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADiceTownGameMode::ADiceTownGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADiceTownPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}