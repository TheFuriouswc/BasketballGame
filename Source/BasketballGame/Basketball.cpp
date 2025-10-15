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
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));


}


void ABasketball::GetLifetimeReplicatedProps(TArray <FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABasketball, BounceCount);

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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Called"));


	AttachToPlayer(ActorWhoCalled);




}

void ABasketball::AttachToPlayer(ACharacter* ActorWhoCalled)
{
		/*Mesh->SetSimulatePhysics(false);*/
		Mesh->AttachToComponent(ActorWhoCalled->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("handSocket"));
		Multi_SetPramas(ActorWhoCalled);
	
	
}

void ABasketball::Multi_SetPramas_Implementation(ACharacter* ActorWhoCalled)
{
	Mesh->SetSimulatePhysics(false);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Server called"));
	Mesh->SetWorldScale3D(Mesh->GetComponentScale() / ActorWhoCalled->GetMesh()->GetComponentScale());
}



