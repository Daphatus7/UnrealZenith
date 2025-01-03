// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameMonsterHandle.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGameMonsterHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API IGameMonsterHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	/* Called when an enemy is killed */
	virtual void OnMonsterKilled(const FName& MonsterName) = 0;
};
