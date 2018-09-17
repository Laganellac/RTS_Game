// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Lib.h"
#include "RTS_Unit.h"
#include "RTS_Archer.h"

FRTS_UnitStats URTS_Lib::GetUnitStats(EUnitName a_UnitName, ETeamColor a_TeamColor)
{
	FRTS_UnitStats statsStruct;
	statsStruct.TeamColor = ETeamColor::NONE;

	if (a_UnitName == EUnitName::ARCHER)
	{
		statsStruct.AttackSpeed = 1.f;
		statsStruct.Cost = 100;
		statsStruct.Damage = 10.f;
		statsStruct.Range = 500.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 100.f;
		statsStruct.TotalHealth = 100.f;
		statsStruct.UnitName = EUnitName::ARCHER;
		statsStruct.UnitClass = ARTS_Archer::StaticClass();
	}


	return statsStruct;
}