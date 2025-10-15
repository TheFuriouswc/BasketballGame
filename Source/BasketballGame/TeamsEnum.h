// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TeamsEnum.generated.h"


UENUM(BlueprintType)
enum class ETeamsEnum : uint8
{
	HomeTeam UMETA(DisplayName = "Home Team"),
	AwayTeam UMETA(DisplayName = "Away Team")



};