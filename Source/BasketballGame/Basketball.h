// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractInterface.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Basketball.generated.h"


UCLASS()
class BASKETBALLGAME_API ABasketball : public AActor, public IInteractInterface
{
	GENERATED_BODY()

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
