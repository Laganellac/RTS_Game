// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_General.h"


ARTS_General::ARTS_General()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::GENERAL);
}

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

void ARTS_General::SetTeamColor(ETeamColor a_TeamColor)
{
	ARTS_Unit::SetTeamColor(a_TeamColor);

	// A general buffs his own units
	m_Stats.TeamColor = a_TeamColor;
	m_TargetColor = a_TeamColor;
}
