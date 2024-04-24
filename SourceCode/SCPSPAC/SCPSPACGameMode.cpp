// Copyright Epic Games, Inc. All Rights Reserved.

#include "SCPSPACGameMode.h"
#include "SCPSPACCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASCPSPACGameMode::ASCPSPACGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
