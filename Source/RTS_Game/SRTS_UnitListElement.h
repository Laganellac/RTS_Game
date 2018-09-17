// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */

class RTS_GAME_API SRTS_UnitListElement : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRTS_UnitListElement)
	{}
	SLATE_ARGUMENT(FRTS_UnitStats, UnitStatsArg)
	SLATE_ARGUMENT(TWeakObjectPtr<class ARTS_PlayerController>, CurrentControllerArg)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	FReply OnClicked() const;

	FText GetCostText() const;

	FText GetDamageText() const;

	FText GetHealthText() const;

	FSlateBrush GetIcon() const;

	FText GetRangeText() const;

	TWeakObjectPtr<class ARTS_PlayerController> m_CurrentController;
	FRTS_UnitStats m_UnitStats;
};
