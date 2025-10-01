// Fill out your copyright notice in the Description page of Project Settings.


#include "Basketball.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Logging/StructuredLog.h"

// Sets default values
ABasketball::ABasketball()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetIsReplicated(true);
	


}

void ABasketball::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeprops) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeprops);

	/*DOREPLIFETIME(ABasketball);*/
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Called"));


	Server_AttachToPlayer(ActorWhoCalled);




}

void ABasketball::Server_AttachToPlayer_Implementation(ACharacter* ActorWhoCalled)
{
	if (ActorWhoCalled->HasAuthority())
	{
		Mesh->AttachToComponent(ActorWhoCalled->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("handSocket"));
		Mesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Server called"));
	}
	
}

