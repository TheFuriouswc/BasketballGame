// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketballGameGameInstance.h"



void UBasketballGameGameInstance::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register any replicated properties you’ve marked with UPROPERTY(Replicated)
	// Example:
	DOREPLIFETIME(UBasketballGameGameInstance, ServerName);
	DOREPLIFETIME(UBasketballGameGameInstance, ServerMap);
	DOREPLIFETIME(UBasketballGameGameInstance, ServerSlots);
	DOREPLIFETIME(UBasketballGameGameInstance, Password)
	DOREPLIFETIME(UBasketballGameGameInstance, LobbyCode);
	DOREPLIFETIME(UBasketballGameGameInstance, bHasPassword);

}

FString UBasketballGameGameInstance::GenerateLobbyCode()
{




	FString GenerateLobbyCode;
	char Input;
	int flipCoin;
	int randomNumber;
	int max = 9;
	int min = 0;
	for (int i = 0; i < 10; i++)
	{
		flipCoin = FMath::RandRange(0, 100);
		if (flipCoin > 80)
		{
			randomNumber = FMath::RandRange(min, max);
			Input = '0' + randomNumber;
		}
		else
		{
			Input = FMath::RandRange(65, 90);
		}

		GenerateLobbyCode += Input;
	}



	return GenerateLobbyCode;
}


