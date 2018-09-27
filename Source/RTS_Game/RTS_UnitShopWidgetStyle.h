// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "SlateWidgetStyleContainerBase.h"

#include "RTS_UnitShopWidgetStyle.generated.h"

/** Struct used by URTS_UnitShopWidgetStyle
 * @author Christopher Laganella
 */
USTRUCT()
struct RTS_GAME_API FRTS_UnitShopStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FRTS_UnitShopStyle();
	virtual ~FRTS_UnitShopStyle();

	// FSlateWidgetStyle
	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FRTS_UnitShopStyle& GetDefault();

	UPROPERTY(EditAnywhere, Category = Main)
	FSlateBrush ArcherIcon;
};

/** Wrapper class for FRTS_UnitShoptStle. For injecting style into unit shop UI... unused currently
 * @author Christopher Laganella
 */
UCLASS(hidecategories=Object, MinimalAPI)
class URTS_UnitShopWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	/** The actual data describing the widget appearance. */
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FRTS_UnitShopStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast< const struct FSlateWidgetStyle* >( &WidgetStyle );
	}
};
