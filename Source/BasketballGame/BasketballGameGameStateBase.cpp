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
}

void ABasketballGameGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Delta = DeltaTime;

}

void ABasketballGameGameStateBase::MatchTimer_Implementation()
{

	if (Seconds <= 0)
	{
		Seconds = 59.0f;
		Minutes -= Delta;
		if (Minutes < 0.0f)
		{
			Seconds = 0;
			Minutes = 0;
		}
	}
	else
	{
		if (Seconds == 0 && Minutes == 0)
		{

		}
		Seconds -= Delta;

		if (Seconds < 0.0f)
		{
			Seconds += 59.0f;
			Minutes -= 1.0f;

			if (Minutes < 0.0f)
			{
				Minutes = 0.0f;
				Seconds = 0.0f;
			}
		}
	}


}

