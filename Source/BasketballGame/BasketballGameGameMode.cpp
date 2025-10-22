// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasketballGameGameMode.h"
#include "BasketballGameCharacter.h"
#include "Net/UnrealNetwork.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/HUD.h"

void ABasketballGameGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasketballGameGameMode, HomeTeamScore);
	DOREPLIFETIME(ABasketballGameGameMode, AwayTeamScore);

}

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
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_BasketballPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
	
	/*static ConstructorHelpers::FClassFinder<AGameStateBase> GameGameStateBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_BasketballGameGameState"));
	if (GameGameStateBPClass.Class != NULL)
	{
		GameStateClass = GameGameStateBPClass.Class;
	}*/


}
