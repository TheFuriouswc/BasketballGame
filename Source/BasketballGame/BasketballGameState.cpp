// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketballGameState.h"

void ABasketballGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasketballGameState, HomeTeamScoreState);
	DOREPLIFETIME(ABasketballGameState, AwayTeamScoreState);
}

void ABasketballGameState::OnRep_HomeTeamScoreState()
{

}

void ABasketballGameState::OnRep_AwayTeamScoreState()
{

}
