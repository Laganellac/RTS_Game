// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_UserInterface.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#include "RTS_HUD.h"
#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"


#define LOCTEXT_NAMESPACE "SRTS_UserInterface"

void SRTS_UserInterface::Construct(const FArguments& InArgs)
{
	// Example
	
	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.VAlign(VAlign_Top)
		.HAlign(HAlign_Center)
		[
			// Inside lies a text block with these settings 
			SNew(STextBlock)
			.ShadowColorAndOpacity(FLinearColor::Black)
			.ColorAndOpacity(FLinearColor::Red) 
			.ShadowOffset(FIntPoint(-1, 1)) 
			.Font(FSlateFontInfo("Veranda", 16))
			//localized text to be translated with a generic name HelloSlateText
			.Text(LOCTEXT("HelloSlateText", "Hello, slate! ... Seeing what happens when I make this string really really really long"))
		]
	];

	
	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
