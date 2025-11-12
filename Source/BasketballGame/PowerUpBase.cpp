// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpBase.h"
#include "Components/CapsuleComponent.h"

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

}

