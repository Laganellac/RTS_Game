// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_Lib.generated.h"

/** Header for defining structs and enums used everywhere within the code
 * @author Christopher Laganella
 */

// Holds all the different types of units
UENUM(BlueprintType, Meta = (Bitflags))
enum class EUnitName : uint8
{
	NONE,
	ARCHER,
	SWORDSMAN,
	HEALER,
	GENERAL,
	DEFENSE_TOWER,
	BANK,
	POINT,
};

/**
* Holds different team color values
* @author Christopher Laganella
*/
UENUM(BlueprintType, Meta = (Bitflags))
enum class ETeamColor : uint8
{
	NONE,
	RED,
	BLUE,
	BLACK,
	WHITE,
	ALL,
};

/**
* Holds all stats relevent to a unit. Defaults to 0.f 
* @author Christopher Laganella
*/
USTRUCT(BlueprintType)
struct FRTS_UnitStats
{
	GENERATED_BODY()

	UPROPERTY()
	FString UnitNameString = "";

	UPROPERTY()
	FString UnitDescription = "";

	UPROPERTY(VisibleAnywhere)
	EUnitName UnitName = EUnitName::NONE;

	UPROPERTY(VisibleAnywhere)
	ETeamColor TeamColor = ETeamColor::NONE;

	UPROPERTY(VisibleAnywhere)
	int Cost = 0;
	
	// Health variables
	// Total health amount
	UPROPERTY(VisibleAnywhere)
	float TotalHealth = 0.f;
	// Current health amount
	UPROPERTY(VisibleAnywhere)
	float CurrentHealth = 0.f;

	// Energy variables
	// Total energy amount
	UPROPERTY(VisibleAnywhere)
	float TotalEnergy = 0.f;
	// Current energy amount
	UPROPERTY(VisibleAnywhere)
	float CurrentEnergy = 0.f;

	// Combat variables
	// How much damage this unit does when attack is called
	UPROPERTY(VisibleAnywhere)
	float Damage = 0.f;
	// Range in engine units (meters?)
	UPROPERTY(VisibleAnywhere)
	float Range = 0.f;
	// How long the lockout between attacks is for this unit (seconds)
	UPROPERTY(VisibleAnywhere)
	float AttackSpeed = 0.f;

	// Mobility variables
	//Determines how fast this unit can move
	UPROPERTY(VisibleAnywhere)
	float Speed = 0.f;
};

/**
* Holds all the stats relevent to the player
* @author Christopher Laganella
*/
USTRUCT(BlueprintType)
struct FRTS_PlayerStats
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	ETeamColor TeamColor = ETeamColor::NONE;

	// Gold Variables
	UPROPERTY(VisibleAnywhere)
	int32 CurrentGold = 0;

	int32 TotalGoldEarned = 0;
	int32 TotalGoldSpent = 0;
};

/**
* A static class used for defining functions to be used by all RTS classes
*/
UCLASS()
class RTS_GAME_API URTS_Lib : public UObject
{
	GENERATED_BODY()

public:
	static FRTS_UnitStats GetUnitStats(EUnitName a_UnitType, ETeamColor a_TeamColor = ETeamColor::NONE);
};
