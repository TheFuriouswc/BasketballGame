// Fill out your copyright notice in the Description page of Project Settings.


#include "Basketball.h"
#include "GameFramework/Character.h"

// Sets default values
ABasketball::ABasketball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MEsh"));
	Mesh->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ABasketball::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasketball::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABasketball::CallInteract(ACharacter* ActorWhoCalled)
{


	Mesh->AttachToComponent(ActorWhoCalled->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, FName("handSocket"));




}

