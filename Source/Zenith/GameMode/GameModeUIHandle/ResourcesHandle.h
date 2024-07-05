// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Zenith/Inventory/Resource.h"
#include "ResourcesHandle.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UResourcesHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API IResourcesHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Resources")
	int32 GetResource(const E_ResourceType ResourceType);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Resources")
	void GetResourceValid(const E_ResourceType ResourceType, int32 & Amount, bool & bValid);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Resources")
	void GetResources(TMap<E_ResourceType, int32> & PlayerResources);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Resources")
	void AddResource(const E_ResourceType ResourceType, const int32 Amount);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Resources")
	void RemoveResource(const E_ResourceType ResourceType, const int32 Amount);
};
 