// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_Healer.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/TimerManager.h"

/**
* Sets m_Stats equal to the stats definedd by URTS_Lib for this unit
*/
ARTS_Healer::ARTS_Healer()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::HEALER);
}

/**
* Overwrites ARTS_AttackingUnit::Attack() so that the "attacked" unit is healed
*/
void ARTS_Healer::Attack()
{
	// Can't attack faster than attack speed
	if (GetWorldTimerManager().IsTimerActive(m_AttackLockoutTimer))
	{
		return;
	}

	ARTS_Unit *lowestUnit = m_TargetedUnits[0];

	for (int i = 1; i < m_TargetedUnits.Num(); i++)
	{
		if (m_TargetedUnits[i]->GetCurrentHealth() < lowestUnit->GetCurrentHealth())
		{
			lowestUnit = m_TargetedUnits[i];
		}
	}

	lowestUnit->RecieveDamage(this, m_Stats.Damage);

	// For debugging purposes
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("Attacked ") + m_TargetedUnits[0]->GetName() + TEXT(", current health = ") + FString::SanitizeFloat(m_TargetedUnits[0]->GetCurrentHealth(), 1)));
	}

	GetWorldTimerManager().SetTimer(m_AttackLockoutTimer, m_Stats.AttackSpeed, false);
}

/**
* Overwrites ARTS_Unit::SetTeamColor so that m_TargetTeamColor is updated too
* @param a_TeamColor ETeamColor - The new team color
*/
void ARTS_Healer::SetTeamColor(ETeamColor a_TeamColor)
{
	ARTS_Unit::SetTeamColor(a_TeamColor);

	m_TargetTeamColor = a_TeamColor;
}