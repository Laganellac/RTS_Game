// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "RTS_AttackingUnit.h"
#include "RTS_Healer.generated.h"

/**
 * The class containing the logic for Healer units. To be spawned as blueprint
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_Healer : public ARTS_AttackingUnit
{
	GENERATED_BODY()

public:
	ARTS_Healer();

	virtual void Attack() override;
	
	virtual void SetTeamColor(ETeamColor a_TeamColor) override;

};
