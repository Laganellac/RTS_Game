// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "RTS_AttackingUnit.h"
#include "RTS_Archer.generated.h"

/**
* A class to handdle logic for archer units. To be spawned as blueprint
* @author Christopher Laganella
*/
UCLASS()
class RTS_GAME_API ARTS_Archer : public ARTS_AttackingUnit
{
	GENERATED_BODY()

public:
	ARTS_Archer();

};
