// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AdvancedFriendsGameInstance.h"
#include "Net/UnrealNetwork.h"
#include <tuple>
#include "BasketballGameGameInstance.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FSessionData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FString Server_Name;

	UPROPERTY(BlueprintReadWrite)
	FString Server_Map;

	UPROPERTY(BlueprintReadWrite)
	int32 NumberOfServerSlots;

	UPROPERTY(BlueprintReadWrite)
	FString ServerPassword;

	UPROPERTY(BlueprintReadWrite)
	FString Lobby_Code;

	UPROPERTY(BlueprintReadWrite)
	bool HasPassword;
};





UCLASS()
class BASKETBALLGAME_API UBasketballGameGameInstance : public UAdvancedFriendsGameInstance
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, Category = "Basketball Game | Game Instance")
	FString ServerName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, Category = "Basketball Game | Game Instance")
	FString ServerMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, Category = "Basketball Game | Game Instance")
	int ServerSlots;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, Category = "Basketball Game | Game Instance")
	FString Password;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, Category = "Basketball Game | Game Instance")
	FString LobbyCode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, Category = "Basketball Game | Game Instance")
	bool bHasPassword;

	


public:
	

	UFUNCTION(BlueprintCallable, Category = "Basketball Game | Game Instance")
	FString GenerateLobbyCode();



	
};
