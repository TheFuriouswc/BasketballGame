// Fill out your copyright notice in the Description page of Project Settings.


#include "ThreePointLine.h"

// Sets default values
AThreePointLine::AThreePointLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AThreePointLine::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AThreePointLine, PointsToAward);
}

// Called when the game starts or when spawned
void AThreePointLine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AThreePointLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

