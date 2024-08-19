// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "AttackHandle.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void UpdateWidth(int32 Level);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void UpdateLifetime(int32 Level);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Attack")
	void UpdatePower(int32 Level);
};
