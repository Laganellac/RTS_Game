// Christopher Laganella - Ramapo College of New Jersey senior project

#include "RTS_UnitShopWidgetStyle.h"


FRTS_UnitShopStyle::FRTS_UnitShopStyle()
{
}

FRTS_UnitShopStyle::~FRTS_UnitShopStyle()
{
}

const FName FRTS_UnitShopStyle::TypeName(TEXT("FRTS_UnitShopStyle"));

const FRTS_UnitShopStyle& FRTS_UnitShopStyle::GetDefault()
{
	static FRTS_UnitShopStyle Default;
	return Default;
}

void FRTS_UnitShopStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
	// Add any brush resources here so that Slate can correctly atlas and reference them
	OutBrushes.Add(&ArcherIcon);
}

