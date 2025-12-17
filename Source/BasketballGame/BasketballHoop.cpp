// Fill out your copyright notice in the Description page of Project Settings.


#include "BasketballHoop.h"
#include "Net/UnrealNetwork.h"
#include "Components/CapsuleComponent.h"

void ABasketballHoop::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasketballHoop, Score);
	DOREPLIFETIME(ABasketballHoop, WhoBasketballHooop);
}

// Sets default values
ABasketballHoop::ABasketballHoop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetIsReplicated(true);

	ScoreCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ScoreCapsule"));
	ScoreCapsule->SetupAttachment(Mesh);
	ScoreCapsule->InitCapsuleSize(30.f, 30.f);
	ScoreCapsule->SetGenerateOverlapEvents(true);

	//GameMode = Cast<ABasketballGameGameMode>(GetWorld());


}

// Called when the game starts or when spawned
void ABasketballHoop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasketballHoop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasketballHoop::Server_AddScore_Implementation(ABasketball* Ball)
{
	if (ABasketball* Shootball = Cast<ABasketball>(Ball))
	{


		if (Shootball->PointsToAward.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Score.ThreePoints"))) && Ball)
		{
			Score = 3;
		}
		else if (Shootball->PointsToAward.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Score.OnePoints"))) && Ball)
		{
			Score = 1;
		}


		if (Shootball->TeamWhoOwnsBall.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Team.Home"))) && Ball)
		{
			if (GameState)
			{

				if (Shootball->PS)
				{
					GameState->PlayerStateWhoShot = Shootball->PS;
				}
				




				GameState->HomeTeamScoreState += Score;
		
				if (GameState->PlayerStateWhoShot)
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("PlayerController: %s"), *GameState->PlayerStateWhoShot->GetName()));
				}
				else
				{
					GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("PlayerController: nullptr")));
				}
			

				//if (HasAuthority())
				//{
				//	GameState->OnRep_HomeTeamScoreState();
				//}
				/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Add Score"));*/
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gamemode not valid"));
			}
			
	
		}
		else if (Shootball->TeamWhoOwnsBall.MatchesTagExact(FGameplayTag::RequestGameplayTag(FName("Team.Away"))) && Ball)
		{
			if (GameState)
			{
				GameState->PlayerWhoShot = Shootball->PlayerWhoShot;
				GameState->AwayTeamScoreState += Score;

				/*GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Add Score"));*/

			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Gamemode not valid"));
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Tag doesn't match"));
		}



	}







}

