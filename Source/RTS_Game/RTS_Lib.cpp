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
		statsStruct.UnitNameString = "Archer";
		statsStruct.UnitDescription = "Ranged unit, deals average damage";
	}

	else if (a_UnitName == EUnitName::SWORDSMAN)
	{
		statsStruct.AttackSpeed = 0.5f;
		statsStruct.Cost = 100;
		statsStruct.Damage = 15.f;
		statsStruct.Range = 50.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 100.f;
		statsStruct.TotalHealth = 200.f;
		statsStruct.UnitName = a_UnitName;
		statsStruct.UnitNameString = "Swordsman";
		statsStruct.UnitDescription = "Melee unit, deals a lot of damage";
	}

	else if (a_UnitName == EUnitName::HEALER)
	{
		statsStruct.AttackSpeed = 0.5f;
		statsStruct.Cost = 200;
		statsStruct.Damage = (-5.f);
		statsStruct.Range = 400.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 100.f;
		statsStruct.TotalHealth = 50.f;
		statsStruct.UnitName = a_UnitName;
		statsStruct.UnitNameString = "Healer";
		statsStruct.UnitDescription = "Ranged unit, heals friendly units";
	}

	else if (a_UnitName == EUnitName::GENERAL)
	{
		statsStruct.AttackSpeed = 0.f;
		statsStruct.Cost = 200;
		statsStruct.Damage = 0.f;
		statsStruct.Range = 500.f;
		statsStruct.Speed = 1.f;
		statsStruct.TotalEnergy = 200.f;
		statsStruct.TotalHealth = 150.f;
		statsStruct.UnitName = a_UnitName;
		statsStruct.UnitNameString = "General";
		statsStruct.UnitDescription = "2x nearby unit damage (cannot attack)";
		
	}

	else if (a_UnitName == EUnitName::DEFENSE_TOWER)
	{
		statsStruct.AttackSpeed = 1.5f;
		statsStruct.Cost = 250;
		statsStruct.Damage = 20.f;
		statsStruct.Range = 600.f;
		statsStruct.Speed = 0.f;
		statsStruct.TotalEnergy = 200.f;
		statsStruct.TotalHealth = 300.f;
		statsStruct.UnitName = a_UnitName;
		statsStruct.UnitNameString = "Defense tower";
		statsStruct.UnitDescription = "Immobile tower that hits slow but hard (ranged)";
	}

	else if (a_UnitName == EUnitName::BANK)
	{
		statsStruct.AttackSpeed = 0.f;
		statsStruct.Cost = 200.f;
		statsStruct.Damage = 0.f;
		statsStruct.Range = 0.f;
		statsStruct.Speed = 0.f;
		statsStruct.TotalEnergy = 0.f;
		statsStruct.TotalHealth = 300.f;
		statsStruct.UnitName = a_UnitName;
		statsStruct.UnitNameString = "Bank";
		statsStruct.UnitDescription = "Increases next rounds starting gold";
	}

	else if (a_UnitName == EUnitName::POINT)
	{
		statsStruct.UnitNameString = "Capture Point";
		// Hello
	}

	else
	{
		statsStruct.UnitName = EUnitName::NONE;
		statsStruct.UnitNameString = "INVALID UNIT";
	}

	return statsStruct;
}

