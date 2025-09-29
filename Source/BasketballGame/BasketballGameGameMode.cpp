// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasketballGameGameMode.h"
#include "BasketballGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABasketballGameGameMode::ABasketballGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_BasketBallPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
