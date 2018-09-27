// Christopher Laganella - Ramapo College of New Jersey senior project

#pragma once

#include "CoreMinimal.h"
#include "RTS_Unit.h"
#include "RTS_BuffingUnit.generated.h"


/** A base class that handles the logic for buffing surrounding units
 * @author Christopher Laganella
 */
UCLASS()
class RTS_GAME_API ARTS_BuffingUnit : public ARTS_Unit
{
	GENERATED_BODY()
	
public:
	ARTS_BuffingUnit();
	
protected:
	virtual void BeginPlay() override;

	virtual void Buff(ARTS_Unit *a_TargetUnit);

	virtual void UnBuff(ARTS_Unit *a_TargetUnit);
	
	// Required params (UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32,bool,const FHitResult &)
	UFUNCTION()
	void OnOverlap(UPrimitiveComponent *a_ThisComp, AActor *a_OtherActor, UPrimitiveComponent *a_OtherComp, int32 a_OtherBodyIndex, bool a_bFromSweep, const FHitResult &a_SweepResult);

	// Required params (UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32)
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent *a_ThisComp, AActor *a_OtherActor, UPrimitiveComponent *a_OtherComp, int32 a_OtherBodyIndex);

	class USphereComponent *m_BuffTrigger;

	UPROPERTY(VisibleAnywhere)
	ETeamColor m_TargetColor;
	
	TArray<ARTS_Unit *> m_TargetedUnits;

};

/*
M:\Windows\Documents\Unreal Projects\RTS_Game\Source\RTS_Game\RTS_BuffingUnit.cpp(15) : error C2664 : 'void TBaseDynamicMulticastDelegate<FWeakObjectPtr,void,UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32,bool,const FHitResult &>::__Internal_AddDynamic<ARTS_BuffingUnit>(UserClass *,void (__cdecl ARTS_BuffingUnit::* )(UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32,bool,const FHitResult &),FName)' :
cannot convert argument 2 from 'void (__cdecl ARTS_BuffingUnit::* )(AActor *,UPrimitiveComponent *,int32,bool,const FHitResult &)'
							to 'void (__cdecl ARTS_BuffingUnit::* )(UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32,bool,const FHitResult &)'
							*/

/*
Severity	Code	Description	Project	File	Line	Suppression State
Error	C2664	'void TBaseDynamicMulticastDelegate<FWeakObjectPtr,void,UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32>::__Internal_AddDynamic<ARTS_BuffingUnit>(UserClass *,void (__cdecl ARTS_BuffingUnit::* )(UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32),FName)': 
cannot convert argument 2 from 'void (__cdecl ARTS_BuffingUnit::* )(UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32,bool,const FHitResult &)' 
							to 'void (__cdecl ARTS_BuffingUnit::* )(UPrimitiveComponent *,AActor *,UPrimitiveComponent *,int32)'	

RTS_Game	M:\Windows\Documents\Unreal Projects\RTS_Game\Source\RTS_Game\RTS_BuffingUnit.cpp	17
*/