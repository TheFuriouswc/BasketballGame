// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketballGameGameStateBase.h"

void ABasketballGameGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasketballGameGameStateBase, HomeTeamScoreState);
	DOREPLIFETIME(ABasketballGameGameStateBase, AwayTeamScoreState);
	DOREPLIFETIME(ABasketballGameGameStateBase, hasGameStarted);
}

