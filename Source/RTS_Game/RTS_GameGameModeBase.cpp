// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_GameGameModeBase.h"
#include "RTS_Unit.h"


TArray<FRTS_UnitStats> ARTS_GameGameModeBase::GetTeamAvailableUnitList(ETeamColor a_TeamColor)
{
	TArray<FRTS_UnitStats> unitStats;

	// Defending units
	if (a_TeamColor == ETeamColor::BLUE)
	{
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::SWORDSMAN));
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::ARCHER));
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
