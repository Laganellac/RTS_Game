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



void ARTS_HUD::BeginPlay()
{
	m_CurrentController = Cast<ARTS_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	m_CurrentWidget = SNew(SRTS_StartGameMenu).OwnerHUDArg(this);

	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
	m_CurrentWidget->SetVisibility(EVisibility::Visible);
}

void ARTS_HUD::DrawHUD()
{

}

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

void ARTS_HUD::StartRound()
{
	m_CurrentWidget.Reset();

	m_CurrentWidget = SNew(SRTS_SpawningUnitsHUD).OwnerHUDArg(this).CurrentControllerArg(m_CurrentController);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
}

void ARTS_HUD::StartInGameHUD()
{
	m_CurrentWidget.Reset();

	m_CurrentWidget = SNew(SRTS_UserInterface).OwnerHUDArg(this).CurrentControllerArg(m_CurrentController);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
}

void ARTS_HUD::EndRound(ETeamColor a_Winner)
{
	m_CurrentWidget.Reset();

	m_CurrentWidget = SNew(SRTS_EndRoundScreen).WinningTeamArg(a_Winner);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
	m_CurrentWidget->SetVisibility(EVisibility::Visible);
}
