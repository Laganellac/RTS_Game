// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class RTS_GAME_API SRTS_StartGameMenu : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRTS_StartGameMenu)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class ARTS_HUD>, OwnerHUDArg);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	FReply AttackButtonPressed();

	FReply DefendButtonPressed();

	void HelpPressed();

	void ExitPressed();

	TWeakObjectPtr<class ARTS_HUD> m_OwnerHUD;

};
