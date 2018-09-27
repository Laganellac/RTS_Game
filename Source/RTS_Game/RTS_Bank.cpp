// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_Bank.h"

/**
* Constructs a bank using the stats defined in URTS::Lib
*/
ARTS_Bank::ARTS_Bank()
{
	m_Stats = URTS_Lib::GetUnitStats(EUnitName::BANK);
}

