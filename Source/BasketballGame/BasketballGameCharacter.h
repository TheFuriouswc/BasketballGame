
// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Kismet/GameplayStatics.h"
#include "Basketball.h"
#include "BasketballGameCharacter.generated.h"



class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config = Game)
class ABasketballGameCharacter : public ACharacter
{
	GENERATED_BODY()

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> InputMapping;



	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Interact Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	/** Interact Aim Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AimAction;


	/** Interact Shoot Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ShootAction;


public:
	ABasketballGameCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated = true, meta = (AllowPrivateAccess = "true"))
	float CameraPitch = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, meta = (AllowPrivateAccess = "true"))
	float ShootingPower = 0.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated = true, meta = (AllowPrivateAccess = "true"))
	bool bIsAiming = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated = true, meta = (AllowPrivateAccess = "true"))
	ABasketball* BasketballRef;

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for Interact input */
	void Interact();

	/** Called for aiming */
	void Aim();
	void StopAim();

	/** Called for shooting */
	void Shoot();

	/** Called for looking input */
	void Look(const FInputActionValue& Value);


protected:

	virtual void NotifyControllerChanged() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	void SetCameraLocation();

public:

	virtual void Tick(float DeltaTime) override;

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(Server, Reliable)
	void Server_CalledOnGetLookRotation(float Pitch);

	UFUNCTION(NetMulticast, Reliable)
	void Multi_CalledOnGetLookRotation(float Pitch);

	UFUNCTION(Server, Reliable)
	void Server_CalledOnInteract();

	UFUNCTION(Server, Reliable)
	void Server_CalledOnShootBall(bool IsAiming, ABasketball* BasketballReference);


	UFUNCTION(NetMulticast, Reliable)
	void Multi_CalledOnShootBall(bool IsAiming, ABasketball* BasketballReference);

};