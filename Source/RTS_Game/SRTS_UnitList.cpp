// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_UnitList.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#include "RTS_HUD.h"
#include "RTS_PlayerController.h"
#include "SRTS_UnitListElement.h"
#include "RTS_GameGameModeBase.h"
#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"
#include "Runtime/SlateCore/Public/Brushes/SlateColorBrush.h"

#define LOCTEXT_NAMESPACE "SRTS_UnitListElement"

void SRTS_UnitList::Construct(const FArguments& InArgs)
{
	m_OwnerHUD = InArgs._OwnerHUDArg;
	m_CurrentController = InArgs._CurrentControllerArg;

	TArray<FRTS_UnitStats> unitStats = ARTS_GameGameModeBase::GetTeamAvailableUnitList(m_CurrentController->GetTeamColor());

	ChildSlot
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Top)
	[
		SNew(SVerticalBox)
		
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SHorizontalBox)
			
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]
		]

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SHorizontalBox)
			
			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]

			+ SHorizontalBox::Slot()
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					SNew(SRTS_UnitListElement)
					.UnitStatsArg(unitStats[0])
				]
			]
		]
	];
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
