// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "RTS_BuffingUnit.h"
#include "RTS_General.generated.h"

/**
 * A class to handle the logic for General units. To be spawned as a blueprint
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_General : public ARTS_BuffingUnit
{
	GENERATED_BODY()
	
public:
	ARTS_General();
	
	virtual void Buff(ARTS_Unit *a_TargetUnit) override;

	virtual void UnBuff(ARTS_Unit *a_TargetUnit) override;

	virtual void SetTeamColor(ETeamColor a_teamColor) override;
};
