// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagsManager.h"
#include "Net/UnrealNetwork.h"
#include "ThreePointLine.generated.h"

UCLASS()
class BASKETBALLGAME_API AThreePointLine : public AActor
{
	GENERATED_BODY()
	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();

public:	
	// Sets default values for this actor's properties
	AThreePointLine();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;






	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGameplayTag PointsToAward = TagsManager.RequestGameplayTag(FName("Score"));


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
