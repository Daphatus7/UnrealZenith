// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameStateHandle.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UGameStateHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API IGameStateHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void DawnEvent() = 0;
	virtual void MorningEvent() = 0;
	virtual void NoonEvent() = 0;
	virtual void DuskEvent() = 0;
	virtual void NightEvent() = 0;
	virtual void MidnightEvent() = 0;
};
