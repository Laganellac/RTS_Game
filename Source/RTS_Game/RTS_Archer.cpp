// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_Archer.h"

/**
*  Creates the Archer with the predefined stats in URTS_Lib
*/
ARTS_Archer::ARTS_Archer()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::ARCHER);
}

