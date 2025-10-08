// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasketballGameGameMode.h"
#include "BasketballGameCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

ABasketballGameGameMode::ABasketballGameGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_BasketBallPlayer"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	static ConstructorHelpers::FClassFinder<AHUD> PlayerHudBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_BasketballPlayerHud.BP_BasketballPlayerHud_C"));
	if (PlayerHudBPClass.Class != NULL)
	{
		HUDClass = PlayerHudBPClass.Class;
	}
	


}
