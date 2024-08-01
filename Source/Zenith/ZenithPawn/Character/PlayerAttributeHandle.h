// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerAttributeHandle.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UPlayerAttributeHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API IPlayerAttributeHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//Restore Health
	virtual void IncreaseHealth(float HealthAmount) = 0;
	//Increase Damage
	virtual void IncreaseDamage(float DamageAmount) = 0;
	//Increase Speed
	virtual void IncreaseSpeed(float SpeedAmount) = 0;
};
