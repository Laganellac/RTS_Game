// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_BlueprintRefs.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Engine/Blueprint.h"


/**
* Fetches references to the ::StaticClass() of the blueprint class for each and Adds them to m_BlueprintClasses
*/
URTS_BlueprintRefs::URTS_BlueprintRefs()
{
	AddBlueprint(EUnitName::ARCHER, FString(TEXT("Class'/Game/UnitBP/BP_Archer.BP_Archer_C'")).GetCharArray().GetData());
	AddBlueprint(EUnitName::HEALER, FString(TEXT("Class'/Game/UnitBP/BP_Healer.BP_Healer_C'")).GetCharArray().GetData());
	AddBlueprint(EUnitName::SWORDSMAN, FString(TEXT("Class'/Game/UnitBP/BP_Swordsman.BP_Swordsman_C'")).GetCharArray().GetData());
	AddBlueprint(EUnitName::GENERAL, FString(TEXT("Class'/Game/UnitBP/BP_General.BP_General_C'")).GetCharArray().GetData());
	AddBlueprint(EUnitName::DEFENSE_TOWER, FString(TEXT("Class'/Game/UnitBP/BP_DefenseTower.BP_DefenseTower_C'")).GetCharArray().GetData());
	AddBlueprint(EUnitName::BANK, FString(TEXT("Class'/Game/UnitBP/BP_Bank.BP_Bank_C'")).GetCharArray().GetData());
}

/**
* Fetches a reference to the ::StaticClass() for the specified unit
* @param a_UnitName EUnitName - The type of unit to fetch
* @return UClass * - The ::StaticClass() reference
*/
UClass *URTS_BlueprintRefs::GetBlueprintClass(EUnitName a_UnitName)
{
	return *m_BlueprintClasses.Find(a_UnitName);
}

/**
* Does the dirty work of actually fetching the information from the specified path then stores it in a map
* @param a_UnitName const EUnitName - The key for m_BlueprintClasses to store the reference under
* @param a_Path TCHAR * - The path to get the blueprint::StaticClass() reference from
*/
void URTS_BlueprintRefs::AddBlueprint(const EUnitName &a_UnitName, TCHAR *a_Path)
{
	// NORTORIOUS FOR MAKING BUILD HANG AT 71%
	ConstructorHelpers::FObjectFinder<UClass> Blueprint(a_Path);
	if (Blueprint.Object)
	{
		m_BlueprintClasses.Add(a_UnitName, Blueprint.Object);
	}
	else
	{
		UE_LOG(LogTemp, Fatal, TEXT("Failed to load from path %s"), a_Path);
	}
}
