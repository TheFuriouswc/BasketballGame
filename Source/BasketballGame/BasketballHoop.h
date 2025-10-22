// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Basketball.h"
#include "GameplayTagsManager.h"
#include "Kismet/GameplayStatics.h"
#include "BasketballGameGameMode.h"
#include "BasketballHoop.generated.h"

UCLASS()
class BASKETBALLGAME_API ABasketballHoop : public AActor
{
	GENERATED_BODY()
	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();
public:	
	// Sets default values for this actor's properties
	ABasketballHoop();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UCapsuleComponent* ScoreCapsule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ABasketballGameGameMode* GameMode = Cast<ABasketballGameGameMode>(UGameplayStatics::GetGameMode(GetWorld()));


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Server, Reliable, Category = "Basketball Hoop | Score")
	void Server_AddScore(ABasketball* Ball);


};
