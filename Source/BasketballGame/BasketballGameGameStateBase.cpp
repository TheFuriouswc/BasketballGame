// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketballGameGameStateBase.h"

void ABasketballGameGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{

	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasketballGameGameStateBase, HomeTeamScoreState);
	DOREPLIFETIME(ABasketballGameGameStateBase, AwayTeamScoreState);
	DOREPLIFETIME(ABasketballGameGameStateBase, hasGameStarted);
	DOREPLIFETIME(ABasketballGameGameStateBase, Seconds);
	DOREPLIFETIME(ABasketballGameGameStateBase, Minutes);
	DOREPLIFETIME(ABasketballGameGameStateBase, PlayerWhoShot);
	DOREPLIFETIME(ABasketballGameGameStateBase, PlayerStateWhoShot);
}

void ABasketballGameGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Delta = DeltaTime;

}

void ABasketballGameGameStateBase::MatchTimer_Implementation()
{
	if (Minutes <= 0.0f && Seconds <= 0.0f)
	{
		Minutes = 0.0f;
		Seconds = 0.0f;
		EndMatch();
		return;
	}

	Seconds -= Delta;

	if (Seconds < 0.0f)
	{
		Seconds += 60.0f;
		Minutes -= 1.0f;
	}

	// Clamp to zero in case we overshot
	if (Minutes < 0.0f)
	{
		Minutes = 0.0f;
		Seconds = 0.0f;
		EndMatch();
	}


}

