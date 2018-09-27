// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "RTS_AttackingUnit.h"
#include "RTS_DefenseTower.generated.h"

/**
 * The class for handling the logic of a defense tower. To be spawned as blueprint
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_DefenseTower : public ARTS_AttackingUnit
{
	GENERATED_BODY()
	
public:
	ARTS_DefenseTower();
	
};
