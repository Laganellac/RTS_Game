// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

/**
 * 
 */
class RTS_GAME_API SRTS_UserInterface : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SRTS_UserInterface)
	{}
	SLATE_ARGUMENT(TWeakObjectPtr<class ARTS_HUD>, OwnerHUDArg);
	SLATE_ARGUMENT(class ARTS_PlayerController *, CurrentControllerArg)
	SLATE_ATTRIBUTE(class ARTS_Unit *, CurrentSelectedUnit)
	SLATE_END_ARGS()

	/** Constructs this widget with InArgs */
	void Construct(const FArguments& InArgs);

private:
	class ARTS_Unit *GetCurrentUnit() const;

	FText GetEnergyText() const;

	FText GetNameText() const;

	FText GetHealthText() const;

	class ARTS_PlayerController *m_CurrentController;
	TWeakObjectPtr<class ARTS_HUD> m_OwnerHUD;

	TAttribute<class ARTS_Unit *> m_CurrentUnit;
	TAttribute<float> m_CurrentCapturePercentage;
};
