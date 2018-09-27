// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_StartGameMenu.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#include "RTS_HUD.h"
#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"

#define LOCTEXT_NAMESPACE "SRTS_StartGameMenu"

/**
* Defines the layout of the widget
*/
void SRTS_StartGameMenu::Construct(const FArguments& InArgs)
{

	m_OwnerHUD = InArgs._OwnerHUDArg;

	ChildSlot
	.HAlign(HAlign_Fill)
	.VAlign(VAlign_Fill)
	[
		SNew(SVerticalBox)

		// First element in the list, the title
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
				SNew(STextBlock)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ColorAndOpacity(FLinearColor::Red)
				.ShadowOffset(FIntPoint(-1, 1))
				.Font(FSlateFontInfo("Veranda", 32))

				.Text(LOCTEXT("Welcome text", "Welcome to RTS_Game"))
			]
		]

		// Second element, the attack button
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
				.OnClicked(this, &SRTS_StartGameMenu::AttackButtonPressed)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 32))
					.Text(LOCTEXT("Attack", "Attack"))
				]
			]
		]

		// Third element, the defend button
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
				.OnClicked(this, &SRTS_StartGameMenu::DefendButtonPressed)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 32))
					.Text(LOCTEXT("Defend", "Defend"))
				]
			]
		]

		// Fourth element, the help button
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
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 32))
					//localized text to be translated with a generic name HelloSlateText
					.Text(LOCTEXT("Help", "Help"))
				]
			]
		]

		// Fifth element, the exit button
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
				.OnClicked(this, &SRTS_StartGameMenu::ExitPressed)
				.HAlign(HAlign_Center)
				.VAlign(VAlign_Center)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 32))
					//localized text to be translated with a generic name HelloSlateText
					.Text(LOCTEXT("Exit", "Exit"))
				]
			]
		]

		// Sixth element, blank for now
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Fill)
		[
			SNew(SBorder)
			.BorderBackgroundColor(FLinearColor::Blue)
			.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
		]
	];

	/*
	ChildSlot
	[
		// Populate the widget
	];
	*/
}

/**
* Tells the HUD class that the player wants to attack
* @return FReply::Handled()
*/
FReply SRTS_StartGameMenu::AttackButtonPressed()
{
	m_OwnerHUD->StartGameAttacking();
	return FReply::Handled();
}

/**
* Tells the HUD class that the player wants to defend
* @return FReply::Handled()
*/
FReply SRTS_StartGameMenu::DefendButtonPressed()
{
	m_OwnerHUD->StartGameDefending();
	return FReply::Handled();
}

/**
* Exits the game
* @return FReply::Handled
*/
FReply SRTS_StartGameMenu::ExitPressed()
{
	// Exit the game
	FGenericPlatformMisc::RequestExit(false);
	return FReply::Handled();
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
