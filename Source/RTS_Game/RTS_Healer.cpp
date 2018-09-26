// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_Healer.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Public/TimerManager.h"

ARTS_Healer::ARTS_Healer()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::HEALER);
}

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

void ARTS_Healer::SetTeamColor(ETeamColor a_TeamColor)
{
	ARTS_Unit::SetTeamColor(a_TeamColor);

	m_TargetTeamColor = a_TeamColor;
}