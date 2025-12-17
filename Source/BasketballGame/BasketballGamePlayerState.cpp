// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketballGamePlayerState.h"

void ABasketballGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasketballGamePlayerState, bIsReady);
	DOREPLIFETIME(ABasketballGamePlayerState, PlayerWhoShot);


}

//void ABasketballGamePlayerState::OnRep_bIsReady()
//{
//}
