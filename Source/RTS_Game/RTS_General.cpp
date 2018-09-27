// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_General.h"

/**
* Gets the stats for this type of unit from URTS_Lib
*/
ARTS_General::ARTS_General()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::GENERAL);
}

/**
* Ovewrites the parent buff. Takes a_TargetUnit's damage and adds 10 to it
* @param a_TargetUnit ARTS_Unit * - The unit to recieve the buff
*/
void ARTS_General::Buff(ARTS_Unit *a_TargetUnit)
{
	ARTS_BuffingUnit::Buff(a_TargetUnit);

	FRTS_UnitStats *targetStats = a_TargetUnit->GetUnitStatsForBuff(this);

	if (targetStats->Damage < 0)
	{
		targetStats->Damage -= 10.f;
	}
	else
	{
		targetStats->Damage += 10.f;
	}
}

/**
* Overwrites the parent unbuff. Takes a_TargetUnit's damage and removes 10 from it
* @param a_TargetUnit ARTS_Unit * - The unit to unbuff
*/
void ARTS_General::UnBuff(ARTS_Unit *a_TargetUnit)
{
	ARTS_BuffingUnit::UnBuff(a_TargetUnit);

	FRTS_UnitStats *targetStats = a_TargetUnit->GetUnitStatsForBuff(this);
	if (targetStats->Damage < 0)
	{
		targetStats->Damage += 10.f;
	}
	else
	{
		targetStats->Damage -= 10.f;
	}
}

/**
* Overwrites ARTS_Unit::SetTeamColor so that m_TargetColor is updated
* @param a_TeamColor ETeamColor - The new TeamColor
*/
void ARTS_General::SetTeamColor(ETeamColor a_TeamColor)
{
	ARTS_Unit::SetTeamColor(a_TeamColor);

	// A general buffs his own units
	m_Stats.TeamColor = a_TeamColor;
	m_TargetColor = a_TeamColor;
}
