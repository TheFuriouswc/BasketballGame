// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "BasketballGameGameMode.h"
#include "BasketballGameState.generated.h"

/**
 * 
 */
UCLASS()
class BASKETBALLGAME_API ABasketballGameState : public AGameState
{
	GENERATED_BODY()
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_HomeTeamScoreState, Category = "BasketballGameMode | Score")
	float HomeTeamScoreState = 0;

	UPROPERTY(EditAnywhere, ReplicatedUsing = OnRep_AwayTeamScoreState, Category = "BasketballGameMode | Score")
	float AwayTeamScoreState = 0;

public:

	UFUNCTION()
	void OnRep_HomeTeamScoreState();

	UFUNCTION()
	void OnRep_AwayTeamScoreState();
	
	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetHomeTeamScoreState() const { return HomeTeamScoreState; };
	UFUNCTION(BlueprintPure, Category = "BasketballGameState | Getter Function")
	float GetAwayTeamScoreState() const { return AwayTeamScoreState; };





};
