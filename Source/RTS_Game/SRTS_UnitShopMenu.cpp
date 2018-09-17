// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_UnitShopMenu.h"
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


#define LOCTEXT_NAMESPACE "SRTS_UnitShopMenu"

void SRTS_UnitShopMenu::Construct(const FArguments& InArgs)
{
	
	m_OwnerHUD = InArgs._OwnerHUDArg;
	m_CurrentController = InArgs._CurrentControllerArg;
	m_GoldAmount = TAttribute<int32>(this, &SRTS_UnitShopMenu::GetGoldAmount);

	ChildSlot
	[
		// Populate the widget
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		.Padding(FMargin(0, 100))
		.AutoHeight()
		[
			SNew(SBorder)
			.BorderImage(FCoreStyle::Get().GetBrush("NoBrush"))
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.ShadowColorAndOpacity(FLinearColor::Black)
				.ColorAndOpacity(FLinearColor::Red)
				.ShadowOffset(FIntPoint(-1, 1))
				.Font(FSlateFontInfo("Veranda", 32))
				//localized text to be translated with a generic name HelloSlateText
				.Text(this, &SRTS_UnitShopMenu::GetTeamText)
				
			]
		]

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
		.Padding(FMargin(0, 50))
		.AutoHeight()
		[
			
			SNew(SHorizontalBox)

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SNew(SRTS_UnitList)
				.OwnerHUDArg(m_OwnerHUD)
				.CurrentControllerArg(m_CurrentController)
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.VAlign(VAlign_Center)
			.AutoWidth()
			[
				SNew(SBorder)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Red)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 32))
					//localized text to be translated with a generic name HelloSlateText
					.Text(this, &SRTS_UnitShopMenu::GetGoldText)
				]
			]
		]
	];
}

int32 SRTS_UnitShopMenu::GetGoldAmount() const
{
	return m_CurrentController->GetCurrentGold();
}

FText SRTS_UnitShopMenu::GetGoldText() const
{
	return FText::FromString(FString::Printf(TEXT("Current gold: %d"), m_GoldAmount.Get()));
}

FText SRTS_UnitShopMenu::GetTeamText() const
{
	ETeamColor color = m_CurrentController->GetTeamColor();

	// Blue for defense
	if (color == ETeamColor::BLUE)
	{
		return LOCTEXT("Defending", "You are defending");
	}
	
	// Red for attack
	else if (color == ETeamColor::RED)
	{
		return LOCTEXT("Attacking", "You are attacking");
	}

	// This shouldnt happen...
	else
	{
		return LOCTEXT("Noteam", "Error identifiying team...");
	}
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
