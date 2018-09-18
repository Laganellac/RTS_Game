// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Lib.h"
#include "RTS_Unit.h"
#include "RTS_Archer.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Blueprint.h"

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
	
		// Careful... this block of code has made the project fail to build silently
		//static ConstructorHelpers::FObjectFinder<UClass> ItemBlueprint(TEXT("Class'/Game/UnitBP/BP_Archer.BP_Archer_C'"));
		//if (ItemBlueprint.Object)
		//{
		//	statsStruct.UnitClass = ItemBlueprint.Object;
		//}
	}


	return statsStruct;
}

UClass *URTS_Lib::GetUnitBlueprintClass(EUnitName a_UnitName)
{
	UClass *temp;
	LoadClass<UClass>(temp, TEXT("Archer"), TEXT("Class'/Game/UnitBP/BP_Archer.BP_Archer_C'"));

	if (a_UnitName == EUnitName::ARCHER)
	{
		//return blueprintClasses.Archer;
	}

	//return blueprintClasses.Archer;
}