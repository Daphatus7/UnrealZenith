// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackHandle.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UAttackHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API IAttackHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//increase damage flat
	// base damage + FlatDamage
	virtual void IncreaseDamage(float FlatDamage) {}
	//increase damage percentage
	// base damage * (1 + Percentage/100)
	virtual void IncreaseDamagePercentage(float Percentage) {}
	//increase attack speed
	virtual void IncreaseAttackSpeed(float Percentage){}
	//Add Number of Projectiles per attack
	virtual void IncreaseNumberOfProjectiles(int32 NumberOfProjectiles){}
	//Increase Damage Area
	virtual void IncreaseDamageArea(float DamageArea){}
	//Increase Movement Speed
	virtual void IncreaseMovementSpeed(float MovementSpeed){}
	//Increase Cluster Size
	virtual void IncreaseClusterSize(int32 ClusterSize){}
};
