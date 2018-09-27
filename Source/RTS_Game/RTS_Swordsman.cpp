// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_Swordsman.h"

/**
* Sets m_Stats equal to the proper unit stats using URTS_Lib
*/
ARTS_Swordsman::ARTS_Swordsman()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::SWORDSMAN);
}


