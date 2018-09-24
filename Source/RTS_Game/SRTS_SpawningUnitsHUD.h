// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class RTS_GAME_API SRTS_SpawningUnitsHUD : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRTS_SpawningUnitsHUD)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class ARTS_HUD>, OwnerHUDArg);
	SLATE_ARGUMENT(TWeakObjectPtr<class ARTS_PlayerController>, CurrentControllerArg)
	SLATE_ATTRIBUTE(EUnitName, CurrentUnit)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:

	FText GetText() const;

	TWeakObjectPtr<class ARTS_HUD> m_OwnerHUD;
	TWeakObjectPtr<class ARTS_PlayerController> m_CurrentController;

};
