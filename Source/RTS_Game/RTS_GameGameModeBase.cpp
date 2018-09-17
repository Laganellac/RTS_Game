// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_GameGameModeBase.h"
#include "RTS_Unit.h"


TArray<FRTS_UnitStats> ARTS_GameGameModeBase::GetTeamAvailableUnitList(ETeamColor a_TeamColor)
{
	TArray<FRTS_UnitStats> unitStats;

	// Attacking units
	if (a_TeamColor == ETeamColor::BLUE)
	{
		// test
		FRTS_UnitStats test;
		test.Range = 500;
		test.TotalHealth = 100;
		test.Damage = 10;

		unitStats.Add(test);
	}

	else if (a_TeamColor == ETeamColor::RED)
	{
		// test
		FRTS_UnitStats test;
		test.Range = 500;
		test.TotalHealth = 100;
		test.Damage = 10;

		unitStats.Add(test);
	}

	else
	{

	}

	return unitStats;
}
