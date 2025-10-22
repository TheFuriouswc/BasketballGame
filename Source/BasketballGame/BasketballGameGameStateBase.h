// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "BasketballGameGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "BasketballGameGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class BASKETBALLGAME_API ABasketballGameGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



public:
	UPROPERTY(EditAnywhere, Replicated, Category = "BasketballGameMode | Score")
	float HomeTeamScoreState = 0;

	UPROPERTY(EditAnywhere, Replicated, Category = "BasketballGameMode | Score")
	float AwayTeamScoreState = 0;

public:


	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetHomeTeamScoreState() const { return HomeTeamScoreState; };
	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetAwayTeamScoreState() const { return AwayTeamScoreState; };

};
