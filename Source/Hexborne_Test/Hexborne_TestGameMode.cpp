// Copyright Epic Games, Inc. All Rights Reserved.

#include "Hexborne_TestGameMode.h"
#include "Hexborne_TestCharacter.h"
#include "UObject/ConstructorHelpers.h"

AHexborne_TestGameMode::AHexborne_TestGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
