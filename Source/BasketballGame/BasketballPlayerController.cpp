// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketballPlayerController.h"
#include "Net/UnrealNetwork.h"

void ABasketballPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasketballPlayerController, PlayersTeam);
}
