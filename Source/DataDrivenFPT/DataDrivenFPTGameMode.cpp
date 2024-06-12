// Copyright Epic Games, Inc. All Rights Reserved.

#include "DataDrivenFPTGameMode.h"
#include "DataDrivenFPTCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADataDrivenFPTGameMode::ADataDrivenFPTGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
