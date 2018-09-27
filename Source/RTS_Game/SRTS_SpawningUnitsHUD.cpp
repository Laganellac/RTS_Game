// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_SpawningUnitsHUD.h"
#include "SlateOptMacros.h"
#include "RTS_HUD.h"
#include "RTS_PlayerController.h"
#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"
#include "Runtime/SlateCore/Public/Brushes/SlateColorBrush.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

/**
* Defines the layout of the widget
*/
void SRTS_SpawningUnitsHUD::Construct(const FArguments& InArgs)
{
	m_OwnerHUD = InArgs._OwnerHUDArg;
	m_CurrentController = InArgs._CurrentControllerArg;
	m_CurrentUnit = TAttribute<EUnitName>(this, &SRTS_SpawningUnitsHUD::GetUnitName);
	
	ChildSlot
	[
		// Populate the widget
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Bottom)
		[
			SNew(SBorder)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Bottom)
			[
				SNew(STextBlock)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ColorAndOpacity(FLinearColor::Black)
				.ShadowOffset(FIntPoint(-1, 1))
				.Font(FSlateFontInfo("Veranda", 32))
				.Text(this, &SRTS_SpawningUnitsHUD::GetText)
			]
		]

	];
	
}

/**
* Gets the next unit to be spawned
* @return EUnitName - The name of next unit
*/
EUnitName SRTS_SpawningUnitsHUD::GetUnitName() const
{
	return m_CurrentController->GetNextUnitToSpawn();
}

/**
* Turns the EUnitName into text for the user
* @return FText - The text to display to the user
*/
FText SRTS_SpawningUnitsHUD::GetText() const
{
	FRTS_UnitStats stats = URTS_Lib::GetUnitStats(m_CurrentUnit.Get());
	return FText::FromString(FString::Printf(TEXT("Current unit: %s"), stats.UnitNameString.GetCharArray().GetData()));
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
