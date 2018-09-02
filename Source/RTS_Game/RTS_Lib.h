// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_Lib.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class ETeamColor : uint8
{
	NONE,
	RED,
	BLUE
};

// Holds all stats relevent to a unit. Defaults to 0.f 30 min 9.1.18
USTRUCT(BlueprintType)
struct FRTS_UnitStats
{
	GENERATED_BODY();

	enum ETeamColor TeamColor = ETeamColor::NONE;
	
	// Health variables
	float TotalHealth = 0.f;
	float CurrentHealth = 0.f;

	// Energy variables
	float TotalEnergy = 0.f;
	float CurrentEnergy = 0.f;

	// Combat variables
	float Damage = 0.f;
	float Range = 0.f;

	// Mobility variables
	float Speed = 0.f;
};

// Holds all stats relevent to a player. 10 min 9.1.18
USTRUCT(BlueprintType)
struct FRTS_PlayerStats
{
	GENERATED_BODY();

	enum ETeamColor TeamColor = ETeamColor::NONE;

	// Gold Variables
	int CurrentGold = 0;
	int TotalGoldEarned = 0;
	int TotalGoldSpent = 0;
};

UCLASS()
class RTS_GAME_API URTS_Lib : public UObject
{
	GENERATED_BODY()
	
};
