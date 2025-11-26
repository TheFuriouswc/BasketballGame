// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "GameplayTagsManager.h"
#include "TeamsEnum.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Basketball.generated.h"


UCLASS()
class BASKETBALLGAME_API ABasketball : public AActor, public IInteractInterface
{
	GENERATED_BODY()

	UGameplayTagsManager& TagsManager = UGameplayTagsManager::Get();
	virtual void CallInteract(ACharacter* ActorWhoCalled) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:	
	// Sets default values for this actor's properties
	ABasketball();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Movement)
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, meta = (AllowPrivateAccess = "true"))
	int BounceCount = 0;

	UPROPERTY(EditAnywhere, Replicated, Category = "Player Controller | Players Team")
	ETeamsEnum PlayersTeam;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGameplayTag TeamWhoOwnsBall = TagsManager.RequestGameplayTag(FName("Team"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	FGameplayTag PointsToAward = TagsManager.RequestGameplayTag(FName("Score"));

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated)
	bool OnFire = false;


	FTimerHandle testTimerHandle;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	void AttachToPlayer(ACharacter* ActorWhoCalled);

	UFUNCTION(NetMulticast, Reliable)
	void Multi_SetPramas(ACharacter* ActorWhoCalled);
	

};
