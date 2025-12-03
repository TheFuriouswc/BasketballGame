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
	UPROPERTY(EditAnywhere, Replicated, Category = "BasketballGameStateMode | Score")
	float HomeTeamScoreState = 0;

	UPROPERTY(EditAnywhere, Replicated, Category = "BasketballGameStateMode | Score")
	float AwayTeamScoreState = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "BasketballGameStateMode | Timer")
	float Minutes = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "BasketballGameStateMode | Timer")
	float Seconds = 0;

	UPROPERTY(EditAnywhere, Replicated, Category = "BasketballGameStateMode | Timer")
	float Delta;



	UPROPERTY(EditAnywhere,BlueprintReadWrite, Replicated, Category = "BasketballGameStateMode | Game Logic")
	bool hasGameStarted = false;

public:

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetHomeTeamScoreState() const { return HomeTeamScoreState; };
	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetAwayTeamScoreState() const { return AwayTeamScoreState; };

	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetMatachTimerMinutes() const { return Minutes; };
	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetMatachTimerSeconds() const { return Seconds; };




	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "BasketballGameState | Game Logic")
	void MatchTimer();

};
