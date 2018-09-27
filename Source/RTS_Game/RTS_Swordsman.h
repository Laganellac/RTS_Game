// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "RTS_AttackingUnit.h"
#include "RTS_Swordsman.generated.h"

/**
 * Class containing logic for swordsmen units. Should be spawned using blueprint
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_Swordsman : public ARTS_AttackingUnit
{
	GENERATED_BODY()

public:
	ARTS_Swordsman();
	
	
};
