// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackPropertyHandle.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAttackPropertyHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API IAttackPropertyHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ApplyFlatDamage(float Amount);
	virtual void ApplyDamageIncreasePercentage(float Amount);
	virtual void ApplyNumberOfProjectiles(const int32 Amount);
	virtual void ApplyDamageArea(const float Amount);
	virtual void ApplyMovementSpeed(const float Amount);
	virtual void ApplyNumberOfClusters(const int32 Amount);
	virtual void ApplyAttackSpeed(const float Amount);
	virtual void ApplyPierceCount(const int32 Amount);
	virtual void ApplyOffCenterDistance(const float Amount);
	virtual void ApplyClusterSize(const int32 Amount);
	virtual void ApplyEffectEnhanced(const float Amount);
	virtual void ApplyCriticalStrikeChance(const float Amount);
};
