// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_HUD.h"
#include "RTS_PlayerController.h"
#include "SRTS_UserInterface.h"
#include "Runtime/Slate/Public/Widgets/SWeakWidget.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"



void ARTS_HUD::BeginPlay()
{
	m_UIWidget = SNew(SRTS_UserInterface).OwnerHUDArg(this);

	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(m_UIWidget.ToSharedRef()));
	m_UIWidget->SetVisibility(EVisibility::Visible);
}

void ARTS_HUD::DrawHUD()
{

}