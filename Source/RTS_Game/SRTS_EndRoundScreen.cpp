// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_EndRoundScreen.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#include "RTS_HUD.h"
#include "RTS_PlayerController.h"
#include "SRTS_UnitList.h"
#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"
#include "Runtime/SlateCore/Public/Brushes/SlateColorBrush.h"

#define LOCTEXT_NAMESPACE "SRTS_EndRoundScreen"

void SRTS_EndRoundScreen::Construct(const FArguments& InArgs)
{
	m_WinningTeam = InArgs._WinningTeamArg;

	ChildSlot
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			[
				SNew(STextBlock)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ColorAndOpacity(FLinearColor::Black)
				.ShadowOffset(FIntPoint(-1, 1))
				.Font(FSlateFontInfo("Veranda", 32))
				.Text(this, &SRTS_EndRoundScreen::GetText)
			]
		]

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::Blue)
			.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(SButton)
				.ClickMethod(EButtonClickMethod::DownAndUp)
				.ContentPadding(FMargin(20, 10))
				.OnClicked(this, &SRTS_EndRoundScreen::ExitPressed)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 32))
					.Text(LOCTEXT("Exit", "Exit"))
				]
			]
		]
	];
	
}

FReply SRTS_EndRoundScreen::ExitPressed() const
{
	// Exit the game
	FGenericPlatformMisc::RequestExit(false);
	return FReply::Handled();
}

FText SRTS_EndRoundScreen::GetText() const
{
	if (m_WinningTeam == ETeamColor::RED)
	{
		return LOCTEXT("AttackWin", "ATTACKING TEAM WINS!");
	}
	else
	{
		return LOCTEXT("DefenseWin", "DEFENDING TEAM WINS!");
	}
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
