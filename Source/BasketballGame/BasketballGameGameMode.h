// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BasketballGameGameMode.generated.h"

UCLASS(minimalapi)
class ABasketballGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	ABasketballGameGameMode();


	UPROPERTY(EditAnywhere, Replicated, Category = "BasketballGameMode | Score")
	float HomeTeamScore = 0;

	UPROPERTY(EditAnywhere, Replicated, Category = "BasketballGameMode | Score")
	float AwayTeamScore = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "BasketballGameMode | Score")
	bool bStartGame = false;



public:
	UFUNCTION(BlueprintPure, Category = "BasketballGameMode | Getter Function")
	float GetHomeTeamScore() const { return HomeTeamScore; };
	UFUNCTION(BlueprintPure, Category = "BasketballGameMode | Getter Function")
	float GetAwayTeamScore() const { return AwayTeamScore; };



};



