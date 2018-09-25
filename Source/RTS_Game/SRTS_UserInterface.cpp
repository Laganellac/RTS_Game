// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_UserInterface.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#include "RTS_HUD.h"
#include "RTS_Unit.h"
#include "RTS_PlayerController.h"
#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"


#define LOCTEXT_NAMESPACE "SRTS_UserInterface"

void SRTS_UserInterface::Construct(const FArguments& InArgs)
{
	m_OwnerHUD = InArgs._OwnerHUDArg;
	m_CurrentController = InArgs._CurrentControllerArg;
	m_CurrentUnit = TAttribute<ARTS_Unit *>(this, &SRTS_UserInterface::GetCurrentUnit);
	
	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SVerticalBox)

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Left)
		.VAlign(VAlign_Bottom)
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Top)
			[
				SNew(SBorder)
				[
					// Inside lies a text block with these settings 
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 16))
					.Text(this, &SRTS_UserInterface::GetNameText)
				]
			]


			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			[
				SNew(SBorder)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 16))
					.Text(this, &SRTS_UserInterface::GetHealthText)
					]
				]

			+ SVerticalBox::Slot()
			.HAlign(HAlign_Left)
			.VAlign(VAlign_Bottom)
			[
				SNew(SBorder)
				[
					SNew(STextBlock)
					.ShadowColorAndOpacity(FLinearColor::Black)
					.ColorAndOpacity(FLinearColor::Black)
					.ShadowOffset(FIntPoint(-1, 1))
					.Font(FSlateFontInfo("Veranda", 16))
					.Text(this, &SRTS_UserInterface::GetEnergyText)
				]
			]
		]
	];
}

ARTS_Unit *SRTS_UserInterface::GetCurrentUnit() const
{
	return m_CurrentController->GetSelectedUnit();
}

FText SRTS_UserInterface::GetEnergyText() const
{
	if (m_CurrentUnit.Get())
	{
		return FText::FromString(FString::Printf(TEXT("Current energy %0.f / %0.f"), m_CurrentUnit.Get()->GetCurrentEnergy(), m_CurrentUnit.Get()->GetTotalEnergy()));
	}
	return FText();
}

FText SRTS_UserInterface::GetNameText() const
{
	if (m_CurrentUnit.Get())
	{
		return FText::FromString(FString::Printf(TEXT("Controlling : %s"), m_CurrentUnit.Get()->GetUnitNameAsString().GetCharArray().GetData()));
	}
	return FText();
}

FText SRTS_UserInterface::GetHealthText() const
{
	if (m_CurrentUnit.Get())
	{
		return FText::FromString(FString::Printf(TEXT("Current HP %0.f / %0.f"), m_CurrentUnit.Get()->GetCurrentHealth(), m_CurrentUnit.Get()->GetTotalHealth()));
	}
	return FText();
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
