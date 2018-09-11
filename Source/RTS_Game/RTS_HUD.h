// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RTS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class RTS_GAME_API ARTS_HUD : public AHUD
{
	GENERATED_BODY()
		
public:
	virtual void BeginPlay() override;

	virtual void DrawHUD() override;

	TSharedPtr<class SRTS_UserInterface> m_UIWidget;
private:

};

