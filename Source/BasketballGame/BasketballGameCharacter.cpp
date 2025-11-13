// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasketballGameCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Components/ArrowComponent.h"
#include "DrawDebugHelpers.h"     
#include "CollisionQueryParams.h" 
#include "GameFramework/ProjectileMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "InteractInterface.h"
#include "Logging/StructuredLog.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ABasketballGameCharacter

ABasketballGameCharacter::ABasketballGameCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;


	

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh(), FName("head"));
	CameraBoom->SocketOffset = FVector(15.0f, 0.0f, 8.0f);
	CameraBoom->TargetArmLength = 0.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = false; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->FieldOfView = 100.0f;
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)






}

//////////////////////////////////////////////////////////////////////////
// Input

void ABasketballGameCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}


void ABasketballGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//checks to see it the player is aiming
	if (bIsAiming)
	{
		//adds the amout of deltatime to figure how long the button is pressed
		ShootingPower += DeltaTime;
		
		//resets
		if (ShootingPower >= 2.0f)
		{
			ShootingPower = 0;
		}
		ShootingPower = FMath::Clamp(ShootingPower, 0.0f, 2.0f);
	}


	if (bIsSprinting && !bIsOutOfStamina && GetCharacterMovement()->Velocity.Length() > 0)
	{
		Stamina -= DeltaTime;
		if (Stamina <= 0)
		{
			bIsOutOfStamina = true;
			bIsSprinting = false;
			GetCharacterMovement()->MaxWalkSpeed = 300.f;
		}
		Stamina = FMath::Clamp(Stamina, 0.0f, 10.0f);
	}
	else if (Stamina <= 3)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Set speed to 300"));
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
	}
	else if (Stamina > 3)
	{
		GetCharacterMovement()->MaxWalkSpeed = 600.f;
	}

	if (bRegenStamina)
	{
		Stamina += DeltaTime;
		bIsOutOfStamina = false;
		if (Stamina >= MaxStamina)
		{
			bRegenStamina = false;
		}
		Stamina = FMath::Clamp(Stamina, 0.0f, 10.0f);
	}
}

void ABasketballGameCharacter::Server_CalledOnSprint_Implementation()
{
	if (Stamina >= 3 && !bIsOutOfStamina)
	{
		bRegenStamina = false;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("set speed to 900"));
		GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
		bIsSprinting = true;
	}
}


void ABasketballGameCharacter::Server_CalledOnStopSprint_Implementation()
{
	if (Stamina >= 3 && !bIsOutOfStamina)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Set speed to 600"));
		GetCharacterMovement()->MaxWalkSpeed = 600.f;

	}
	bIsSprinting = false;
	bRegenStamina = true;
}


void ABasketballGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{


	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABasketballGameCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABasketballGameCharacter::Look);

		//Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ABasketballGameCharacter::Interact);

		//Aim
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &ABasketballGameCharacter::Aim);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &ABasketballGameCharacter::StopAim);

		//shoot
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ABasketballGameCharacter::Shoot);

		//Sprint
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, this, &ABasketballGameCharacter::Sprint);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ABasketballGameCharacter::StopSprint);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ABasketballGameCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ABasketballGameCharacter::Shoot()
{



	Server_CalledOnShootBall(bIsAiming, BasketballRef, FollowCamera, ShootingPower);

	
	


}

void ABasketballGameCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
	//Set CameraPitch
	Server_CalledOnGetLookRotation(GetControlRotation().Pitch);
}

void ABasketballGameCharacter::Interact()
{

	Server_CalledOnInteract();
	
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Interact button fired"));
	

}

void ABasketballGameCharacter::Aim()
{
	

	bIsAiming = true;

}

void ABasketballGameCharacter::StopAim()
{

	ShootingPower = 0.0f;
	bIsAiming = false;
}

void ABasketballGameCharacter::Sprint()
{
	Server_CalledOnSprint();
	
	
}

void ABasketballGameCharacter::StopSprint()
{
	Server_CalledOnStopSprint();
	
}



void ABasketballGameCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Register any replicated properties you’ve marked with UPROPERTY(Replicated)
	// Example:
	DOREPLIFETIME(ABasketballGameCharacter, CameraPitch);
	DOREPLIFETIME(ABasketballGameCharacter, ShootingPower);
	DOREPLIFETIME(ABasketballGameCharacter, bIsAiming);
	DOREPLIFETIME(ABasketballGameCharacter, BasketballRef);
	DOREPLIFETIME(ABasketballGameCharacter, Stamina);
	DOREPLIFETIME(ABasketballGameCharacter, MaxStamina);
	DOREPLIFETIME(ABasketballGameCharacter, bIsSprinting);
	DOREPLIFETIME(ABasketballGameCharacter, bIsOutOfStamina);
	DOREPLIFETIME(ABasketballGameCharacter, bRegenStamina);
	DOREPLIFETIME(ABasketballGameCharacter, PlayersTeam);
	DOREPLIFETIME(ABasketballGameCharacter, PointsToAwardPlayer);
	DOREPLIFETIME(ABasketballGameCharacter, MaxSprintSpeed);
}



void  ABasketballGameCharacter::Server_CalledOnGetLookRotation_Implementation(float Pitch)
{
	Multi_CalledOnGetLookRotation(Pitch);
}

void ABasketballGameCharacter::Multi_CalledOnGetLookRotation_Implementation(float Pitch)
{
	CameraPitch = Pitch;
}


void  ABasketballGameCharacter::Server_CalledOnInteract_Implementation()
{

	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = (FollowCamera->GetForwardVector() * 300) + Start;


	FCollisionQueryParams RV_TraceParams(FName(TEXT("RV_Trace")), true, this);
	RV_TraceParams.bTraceComplex = true;
	RV_TraceParams.bReturnPhysicalMaterial = false;
	RV_TraceParams.AddIgnoredActor(this);


	// Initialize hit info
	FHitResult RV_Hit(ForceInit);


	bool bHit = GetWorld()->LineTraceSingleByChannel
	(
		RV_Hit,       // result
		Start,        // start
		End,          // end
		ECC_Visibility,     // collision channel
		RV_TraceParams
	);

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);

	// Check result
	if (bHit && RV_Hit.bBlockingHit)
	{

		AActor* HitActor = RV_Hit.GetActor();
		FVector ImpactPoint = RV_Hit.ImpactPoint;
		FVector ImpactNormal = RV_Hit.ImpactNormal;

		IInteractInterface* InteractableActor = Cast<IInteractInterface>(HitActor);



		if (InteractableActor)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Interact with an object"));
			BasketballRef = Cast<ABasketball>(HitActor);
			BasketballRef->SetOwner(this);
			InteractableActor->CallInteract(this);

		}
	}




}

void ABasketballGameCharacter::Server_CalledOnShootBall_Implementation(bool IsAiming, ABasketball* BasketballReference, UCameraComponent* Camera, float ShootPower)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Shoot ball Server"));




	if (IsAiming && BasketballReference)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Kobe!"));
		
		BasketballReference->PointsToAward = PointsToAwardPlayer;
		
		if (BasketballRef->Mesh->IsAttachedTo(this->GetMesh()))
		{
			BasketballReference->Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
			
		}
	/*	BasketballReference->Mesh->SetupAttachment(BasketballReference->GetRootComponent());*/
		
		//Launch Angle
		FRotator LaunchRot = Camera->GetComponentRotation();
		LaunchRot.Pitch += 35.0f;
		FVector ShootDirection = LaunchRot.Vector();

		//Get abount of impluse to add from center of the camera * the shooting power
		FVector Power = ShootDirection * ShootPower * 1000.0f;

		BasketballReference->Mesh->SetSimulatePhysics(true);

		BasketballReference->ProjectileMovementComponent->bShouldBounce = true;
		BasketballReference->Mesh->AddImpulse(Power, NAME_None, true);
	}
	else if (BasketballReference)
	{
		ShootingPower = 0.50f;
		
		BasketballReference->PointsToAward = PointsToAwardPlayer;

		if (BasketballRef->Mesh->IsAttachedTo(this->GetMesh()))
		{
			BasketballReference->Mesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		}
		/*BasketballReference->Mesh->SetupAttachment(BasketballReference->GetRootComponent());*/


		//Launch Anle
		FRotator LaunchRot = Camera->GetComponentRotation();
		LaunchRot.Pitch += 45.0f;
		FVector ShootDirection = LaunchRot.Vector();

		//Get abount of impluse to add from center of the camera * the shooting power
		FVector Power = ShootDirection * ShootingPower * 1000.0f;

		BasketballReference->Mesh->SetSimulatePhysics(true);

		BasketballReference->ProjectileMovementComponent->bShouldBounce = true;
		BasketballReference->Mesh->AddImpulse(Power, NAME_None, true);


	}





	Multi_CalledOnShootBall(IsAiming, BasketballReference);





}


void ABasketballGameCharacter::Multi_CalledOnShootBall_Implementation(bool IsAiming, ABasketball* BasketballReference)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, TEXT("Shoot ball client"));



	if (IsAiming && BasketballReference)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Kobe!"));



		BasketballReference->Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BasketballReference->Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		

		



		BasketballRef = nullptr;

	}
	else if (BasketballRef)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Kobe!"));

	

		BasketballReference->Mesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		BasketballReference->Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);






		BasketballRef = nullptr;
	}


}

