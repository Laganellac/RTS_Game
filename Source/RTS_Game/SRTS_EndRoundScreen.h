// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class RTS_GAME_API SRTS_EndRoundScreen : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRTS_EndRoundScreen)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class ARTS_HUD>, OwnerHUDArg);
	SLATE_ARGUMENT(ETeamColor, WinningTeamArg);
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	FReply ExitPressed() const;

	FText GetText() const;

	ETeamColor m_WinningTeam;
};
