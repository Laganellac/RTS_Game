// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_GameGameModeBase.h"
#include "RTS_Unit.h"


/**
* Constructs an array of units that are available to the given team
* @param a_TeamColor ETeamColor - The color of the team in question
* @return TArray<FRTS_UnitStats> - A list of the units available ot the team
*/
TArray<FRTS_UnitStats> ARTS_GameGameModeBase::GetTeamAvailableUnitList(ETeamColor a_TeamColor)
{
	TArray<FRTS_UnitStats> unitStats;

	// Defending units
	if (a_TeamColor == ETeamColor::BLUE)
	{
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::SWORDSMAN));
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::ARCHER));
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::DEFENSE_TOWER));
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::BANK));
	}

	// Attacking units
	else if (a_TeamColor == ETeamColor::RED)
	{
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::SWORDSMAN));
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::ARCHER));
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::HEALER));
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::GENERAL));
	}

	else
	{

	}

	return unitStats;
}
