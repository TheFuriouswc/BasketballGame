// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasketballGameCharacter.h"
#include "PowerUpBase.generated.h"

UCLASS()
class BASKETBALLGAME_API APowerUpBase : public AActor
{
	GENERATED_BODY()


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:	
	// Sets default values for this actor's properties
	APowerUpBase();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCapsuleComponent* PickUpCapsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,Replicated, Category = "PowerUpBase | Factors")
	float EnergyDrinkSpeed = 1200;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	float PowerUpTimer = 10.0f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	ABasketballGameCharacter* PlayerWhoHasPowerUp;


protected:

	UPROPERTY(Replicated)
	bool StartPowerupTimer = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_OnDrinkEnergyDrink(ABasketballGameCharacter* PlayerCharacter);

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void Server_ResetWalkSpeed(ABasketballGameCharacter* PlayerCharacter);

};
