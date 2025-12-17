// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Net/UnrealNetwork.h"
#include "BasketballPlayerController.h"
#include "BasketballGamePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BASKETBALLGAME_API ABasketballGamePlayerState : public APlayerState
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_bIsReady, meta = (AllowPrivateAccess = "true"))
	bool bIsReady = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing = OnRep_PlayerWhoShot, meta = (AllowPrivateAccess = "true"))
	ABasketballPlayerController* PlayerWhoShot;

public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_bIsReady();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRep_PlayerWhoShot();

};
