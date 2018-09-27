// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTS_HUD.generated.h"

/** A class for managing the HUD. Chooses which slate widgets are displayed
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_HUD : public AHUD
{
	GENERATED_BODY()
		
public:
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	void StartGameAttacking();

	void StartGameDefending();

	void StartRound();

	void StartInGameHUD();

	void EndRound(ETeamColor a_Winner);

	TSharedPtr<class SCompoundWidget> m_CurrentWidget;
private:

	class ARTS_PlayerController *m_CurrentController;

	TArray<TSharedPtr<class SCompoundWidget>> m_WidgetStack;
};

