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
void SRTS_SpawningUnitsHUD::Construct(const FArguments& InArgs)
{
	m_OwnerHUD = InArgs._OwnerHUDArg;
	m_CurrentController = InArgs._CurrentControllerArg;
	
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
FText SRTS_SpawningUnitsHUD::GetText() const
{
	m_CurrentController->
	return FText();
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
