// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RTS_GameGameModeBase.generated.h"

/** Defines game rules for this game mode
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_GameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	static TArray<FRTS_UnitStats> GetTeamAvailableUnitList(ETeamColor a_TeamColor);
};
