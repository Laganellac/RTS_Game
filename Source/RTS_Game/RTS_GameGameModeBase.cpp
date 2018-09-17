// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_GameGameModeBase.h"
#include "RTS_Unit.h"


TArray<FRTS_UnitStats> ARTS_GameGameModeBase::GetTeamAvailableUnitList(ETeamColor a_TeamColor)
{
	TArray<FRTS_UnitStats> unitStats;

	// Attacking units
	if (a_TeamColor == ETeamColor::BLUE)
	{
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::ARCHER));
	}

	else if (a_TeamColor == ETeamColor::RED)
	{
		unitStats.Add(URTS_Lib::GetUnitStats(EUnitName::ARCHER));
	}

	else
	{

	}

	return unitStats;
}
