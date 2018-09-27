// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "RTS_Lib.h"
#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "RTS_BlueprintRefs.generated.h"

/** A class used to store references to blueprint-types of units
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API URTS_BlueprintRefs : public UObject
{
	GENERATED_BODY()

public:
	URTS_BlueprintRefs();

	UClass *GetBlueprintClass(EUnitName a_UnitName);
	
private:
	void AddBlueprint(const EUnitName &a_UnitName, TCHAR *a_Path);

	TMap<EUnitName, UClass *> m_BlueprintClasses;
};
