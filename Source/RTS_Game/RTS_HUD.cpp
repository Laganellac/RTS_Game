// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_HUD.h"
#include "RTS_PlayerController.h"
#include "SRTS_UserInterface.h"
#include "SRTS_StartGameMenu.h"
#include "SRTS_UnitShopMenu.h"
#include "SRTS_SpawningUnitsHUD.h"
#include "SRTS_EndRoundScreen.h"
#include "Runtime/Slate/Public/Widgets/SWeakWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


/**
* Called when spawned. Acquires m_CurrentController and sets the currentwidget to the SRTS_StartGameMeny
*/
void ARTS_HUD::BeginPlay()
{
	m_CurrentController = Cast<ARTS_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_CurrentWidget = SNew(SRTS_StartGameMenu).OwnerHUDArg(this);

	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
	m_CurrentWidget->SetVisibility(EVisibility::Visible);
}

/**
* a hud's version of tick
*/
void ARTS_HUD::DrawHUD()
{

}

/**
* Changes the widget to SRTS_UnitShopMenu and sets the player controller team color to red
*/
void ARTS_HUD::StartGameAttacking()
{
	// Deletes the current slate widget
	m_CurrentWidget.Reset();

	// Red for attack
	m_CurrentController->SetTeamColor(ETeamColor::RED);	 

	m_CurrentWidget = SNew(SRTS_UnitShopMenu).OwnerHUDArg(this).CurrentControllerArg(m_CurrentController);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
	m_CurrentWidget->SetVisibility(EVisibility::Visible);
}

/**
* Changes the widget to SRTS_UnitShopMenu and sets the player controller team color to blue 
*/
void ARTS_HUD::StartGameDefending()
{
	// Deletes the current slate widget
	m_CurrentWidget.Reset();

	// Red for attack
	m_CurrentController->SetTeamColor(ETeamColor::BLUE);

	m_CurrentWidget = SNew(SRTS_UnitShopMenu).OwnerHUDArg(this).CurrentControllerArg(m_CurrentController);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
	m_CurrentWidget->SetVisibility(EVisibility::Visible);
}

/**
* Sets the current widget to SRTS_SpawningUnitsHUD. Called when its time for the user to begin spawning units
*/
void ARTS_HUD::StartRound()
{
	m_CurrentWidget.Reset();

	m_CurrentWidget = SNew(SRTS_SpawningUnitsHUD).OwnerHUDArg(this).CurrentControllerArg(m_CurrentController);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
}

/**
* Sets the current widget to SRTS_UsreInterface. Called when the round stars
*/
void ARTS_HUD::StartInGameHUD()
{
	m_CurrentWidget.Reset();

	m_CurrentWidget = SNew(SRTS_UserInterface).OwnerHUDArg(this).CurrentControllerArg(m_CurrentController);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
}

/**
* SEts the current widget to SRTS_EndRoundScreen. Called when a team wins the game
* @param a_Winner ETeamColor - The winning team color
*/
void ARTS_HUD::EndRound(ETeamColor a_Winner)
{
	m_CurrentWidget.Reset();

	m_CurrentWidget = SNew(SRTS_EndRoundScreen).WinningTeamArg(a_Winner);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
	m_CurrentWidget->SetVisibility(EVisibility::Visible);
}
