// Christopher Laganella - Ramapo College of New Jersey senior project

#include "SRTS_UnitListElement.h"
#include "RTS_HUD.h"
#include "RTS_PlayerController.h"
#include "Runtime/Engine/Classes/Engine/Texture2D.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

#include "Runtime/Slate/Public/Widgets/Images/SImage.h"
#include "Runtime/SlateCore/Public/Widgets/SBoxPanel.h"
#include "Runtime/Slate/Public/Widgets/Text/STextBlock.h"
#include "Runtime/Slate/Public/Widgets/Input/SButton.h"
#include "Runtime/SlateCore/Public/Styling/CoreStyle.h"
#include "Runtime/SlateCore/Public/Brushes/SlateColorBrush.h"


#define LOCTEXT_NAMESPACE "SRTS_UnitListElement"

void SRTS_UnitListElement::Construct(const FArguments& InArgs)
{
	m_UnitStats = InArgs._UnitStatsArg;
	m_CurrentController = InArgs._CurrentControllerArg;

	//FSlateDynamicImageBrush 
	//FPaths::EngineContentDir() / TEXT("UI/Icons/archerIcon.png")
	//ConstructorHelpers::FObjectFinder<UTexture2D>archerIconAsset(TEXT("Texture2D'/Game/UI/Icons/archerIcon.archerIcon'"));

	ChildSlot
	.HAlign(HAlign_Center)
	.VAlign(VAlign_Top)
	[
		SNew(SVerticalBox)
		
		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SImage)
			//.Image(this, &SRTS_UnitListElement::GetIcon)
		]

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(STextBlock)
			.Text(this, &SRTS_UnitListElement::GetHealthText)
			.ColorAndOpacity(FLinearColor::Black)
			.Font(FSlateFontInfo("Veranda", 18))
		]

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(STextBlock)
			.Text(this, &SRTS_UnitListElement::GetDamageText)
			.ColorAndOpacity(FLinearColor::Black)
			.Font(FSlateFontInfo("Veranda", 18))
		]

		+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Top)
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			.OnClicked(this, &SRTS_UnitListElement::OnClicked)
			.DesiredSizeScale(FVector2D(3.f, 3.f))
			[
				SNew(STextBlock)
				.ColorAndOpacity(FLinearColor::Black)
				.Font(FSlateFontInfo("Veranda", 18))
				.Text(this, &SRTS_UnitListElement::GetCostText)
			]
		]
	];
}

FReply SRTS_UnitListElement::OnClicked() const
{
	if (m_CurrentController->GetCurrentGold() < m_UnitStats.Cost)
	{
		return FReply::Handled();
	}
	else
	{
		m_CurrentController->AddUnit(m_UnitStats.UnitName);
		return FReply::Handled();
	}

	
}

FText SRTS_UnitListElement::GetCostText() const
{
	return FText::FromString(FString::Printf(TEXT("Cost: %d"), m_UnitStats.Cost));
}

FText SRTS_UnitListElement::GetDamageText() const
{
	return FText::FromString(FString::Printf(TEXT("Damage: %f"), m_UnitStats.Damage));
}

FText SRTS_UnitListElement::GetHealthText() const
{
	return FText::FromString(FString::Printf(TEXT("Health: %f"), m_UnitStats.TotalHealth));
}

FSlateBrush SRTS_UnitListElement::GetIcon() const
{
	return FSlateBrush();
}

FText SRTS_UnitListElement::GetRangeText() const
{
	return FText::FromString(FString::Printf(TEXT("Range: &f"), m_UnitStats.Range));
}

#undef LOCTEXT_NAMESPACE

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
