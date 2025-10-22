// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TeamsEnum.h"
#include "BasketballPlayerController.generated.h"

/**
 * 
 */


UCLASS()
class BASKETBALLGAME_API ABasketballPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(EditAnywhere, Replicated, Category = "Player Controller | Players Team")
	ETeamsEnum PlayersTeam = ETeamsEnum::HomeTeam;


	
};
