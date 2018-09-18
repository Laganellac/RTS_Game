// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Lib.h"
#include "RTS_Unit.h"
#include "RTS_Archer.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Blueprint.h"

FRTS_UnitStats URTS_Lib::GetUnitStats(EUnitName a_UnitName, ETeamColor a_TeamColor)
{
	FRTS_UnitStats statsStruct;
	statsStruct.TeamColor = a_TeamColor;

	if (a_UnitName == EUnitName::ARCHER)
	{
		statsStruct.AttackSpeed = 1.f;
		statsStruct.Cost = 150;
		statsStruct.Damage = 10.f;
		statsStruct.Range = 500.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 100.f;
		statsStruct.TotalHealth = 100.f;
		statsStruct.UnitName = a_UnitName;
	}

	else if (a_UnitName == EUnitName::SWORDSMAN)
	{
		statsStruct.AttackSpeed = 0.5f;
		statsStruct.Cost = 100;
		statsStruct.Damage = 15.f;
		statsStruct.Range = 200.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 100.f;
		statsStruct.TotalHealth = 200.f;
		statsStruct.UnitName = a_UnitName;
	}

	else if (a_UnitName == EUnitName::HEALER)
	{
		statsStruct.AttackSpeed = 0.5f;
		statsStruct.Cost = 200;
		statsStruct.Damage = 5.f;
		statsStruct.Range = 400.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 100.f;
		statsStruct.TotalHealth = 50.f;
		statsStruct.UnitName = a_UnitName;
	}

	else if (a_UnitName == EUnitName::GENERAL)
	{
		statsStruct.AttackSpeed = 0.f;
		statsStruct.Cost = 200;
		statsStruct.Damage = 0.f;
		statsStruct.Range = 0.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 200.f;
		statsStruct.TotalHealth = 150.f;
		statsStruct.UnitName = a_UnitName;
	}

	else
	{
		statsStruct.UnitName = EUnitName::NONE;
	}

	return statsStruct;
}

