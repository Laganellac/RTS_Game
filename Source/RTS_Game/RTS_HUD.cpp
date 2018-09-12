// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_HUD.h"
#include "RTS_PlayerController.h"
#include "SRTS_UserInterface.h"
#include "SRTS_StartGameMenu.h"
#include "Runtime/Slate/Public/Widgets/SWeakWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"



void ARTS_HUD::BeginPlay()
{
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

	m_CurrentWidget = SNew(SRTS_UserInterface).OwnerHUDArg(this);
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_CurrentWidget.ToSharedRef()));
	m_CurrentWidget->SetVisibility(EVisibility::Visible);
}
