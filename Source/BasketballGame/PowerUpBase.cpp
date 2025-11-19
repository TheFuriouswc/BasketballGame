// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpBase.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"

void APowerUpBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	DOREPLIFETIME(APowerUpBase, EnergyDrinkSpeed);
	DOREPLIFETIME(APowerUpBase, PowerUpTimer);
	DOREPLIFETIME(APowerUpBase, StartPowerupTimer);
	DOREPLIFETIME(APowerUpBase, PlayerWhoHasPowerUp);

}

// Sets default values
APowerUpBase::APowerUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetIsReplicated(true);

	PickUpCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PickUpCapsule"));
	PickUpCapsule->SetupAttachment(Mesh);
	PickUpCapsule->InitCapsuleSize(30.f, 30.f);
	PickUpCapsule->SetGenerateOverlapEvents(true);



}

// Called when the game starts or when spawned
void APowerUpBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUpBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (StartPowerupTimer && PowerUpTimer > 0)
	{
		PowerUpTimer -= 1;
	}
	PowerUpTimer = FMath::Clamp(PowerUpTimer, 0.0f, 10.0f);

	if (StartPowerupTimer && PowerUpTimer <= 0)
	{
		Server_ResetWalkSpeed(PlayerWhoHasPowerUp);
	}

}

void APowerUpBase::Server_ResetWalkSpeed_Implementation(ABasketballGameCharacter* PlayerCharacter)
{
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->DefaultWalkSpeed;
	PlayerCharacter->MaxSprintSpeed = PlayerCharacter->DefaultMaxSprintSpeed;
	PlayerCharacter->bDrainStamina = true;
	StartPowerupTimer = false;
	PlayerWhoHasPowerUp = nullptr;
	PowerUpTimer = 10.0f;

}

void APowerUpBase::Server_OnDrinkEnergyDrink_Implementation(ABasketballGameCharacter* PlayerCharacter)
{

	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayerCharacter->MaxSprintSpeed;
	PlayerCharacter->MaxSprintSpeed = EnergyDrinkSpeed;
	PlayerCharacter->bDrainStamina = false;
	StartPowerupTimer = true;
	PlayerWhoHasPowerUp = PlayerCharacter;
}

