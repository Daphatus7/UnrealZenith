// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Zenith/Attack/AttackComposite/AttackModifierType.h"
#include "Zenith/Attack/AttackGroup/AttackGroup.h"
#include "Templates/SharedPointer.h"
#include "Zenith/Library/ZenithFunctionLibrary.h"
#include "Zenith/Attack/AttackPropertyHandle.h"
#include "AttackAttribute.generated.h"
/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class ZENITH_API UAttackAttribute : public UObject
{
	GENERATED_BODY()
	/**
	 * Current Attribute Level
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attack Attribute", meta = (AllowPrivateAccess = "true"))
	int32 Level = 1;

	/**
	 * The maximum level of the attribute
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Attribute", meta = (AllowPrivateAccess = "true"))
	int32 TotalLevels = 20;
	/**
     *Attack Attribute type - each attack attribute handles an attribute type
     *
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Attribute", meta = (AllowPrivateAccess = "true"))
    EAttackModifierType AttackAttributeType = EAttackModifierType::None;

	
public:
	void BeginPlay();
	
	EAttackModifierType GetAttackModifierType() const {return AttackAttributeType;}
private:
	/**
	 *A table to load the modification curve
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Table", meta = (AllowPrivateAccess = "true"))
	UCurveTable * AttackLevelTable;

	/**
	 *The data of the curve table
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack Attribute", meta = (AllowPrivateAccess = "true"))
	TArray<float> AttackLevelData;

	/**
	 * Load Attack Data
	 */
	UFUNCTION(BlueprintCallable, Category = "Attack Attribute")
	void LoadAttackLevelData();
	/**
	 * Interface to the attack group
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AttackGroup", meta = (AllowPrivateAccess = "true"))
	AAttackGroup * AttackCluster = nullptr;

	/**
	 * The data of the attack attribute
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interface", meta = (AllowPrivateAccess = "true"))
	TScriptInterface<IAttackPropertyHandle> AttackDataHandle;
	/**
	 * Only get the value, but ignore the context of attribute
	 * @return the return value represents the percentage of 1 (for 100%) of the attribute
	 */
	float GetValue();

protected:
	/**
	 * When Level up, the visual effect will be triggered
	 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Level Up visual effect")
	void LevelUpVisualEffect();

	/**
	* When the attribute is leveled up, the attack will be modified
	*/
	UFUNCTION(BlueprintCallable, Category = "Level Up Data Modify")
	virtual void LevelUpDataModify();
public:
	/**
	 * When the skill is leveled up it will increase the responsible properties of the attack
	 * Certain Level up will have different visual effects.
	 */
	UFUNCTION(BlueprintCallable, Category = "Attack Attribute")
	bool LevelUp();
	/**
	 * Assign the cluster to the attack attribute to modify the behavior of the attack
	 * Also this has some reference to manipulate the Attack Group and Behaviour of attacks
	 */
	void AssignCluster(AAttackGroup * AttackGroup)
	{
		AttackCluster = AttackGroup;
	}

	/**
	 * Assign attack data to manipulate
	 */
	void AssignAttackDataHandle(IAttackPropertyHandle * AttackProperty)
	{
		AttackDataHandle.SetInterface(AttackProperty);
		AttackDataHandle.SetObject(this);
		//Apply modification to the attack data
		LoadAttackLevelData();
		LevelUpDataModify();
		LevelUpVisualEffect();
	}
};
