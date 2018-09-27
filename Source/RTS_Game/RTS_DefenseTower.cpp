// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_DefenseTower.h"

/**
* Sets m_Stats value to as defined as URTS_Lib
*/
ARTS_DefenseTower::ARTS_DefenseTower()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::DEFENSE_TOWER);
}

