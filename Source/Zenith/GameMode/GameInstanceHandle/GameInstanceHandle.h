// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Zenith/GameMode/SaveLoad/ZenithSaveGame.h"
#include "Zenith/Interactable/Interactable.h"
#include "GameInstanceHandle.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
class UGameInstanceHandle : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API IGameInstanceHandle
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	//Check Save Bool
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Retrieve Save Data")
	bool CheckSaveBool();

	//Get Seed
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Retrieve Save Data")
	FRandomStream GetSeed();
	
	//Get Save
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Retrieve Save Data")
	void GetSave(UZenithSaveGame*& OutSaveGame);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Set Save Data")
	void StartNewLevel();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Set Save Data")
	void SaveGame();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Set Save Data")
	void UpdateSaveData();

	/*-----------------------------------Save Player--------------------------------------*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Set Save Data")
	void UpdatePlayerExperience(int32 Experience, int32 Level);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Set Save Data")
	void GetPlayerExperience(int32 & Experience,int32 & ExperienceCap,int32 & Level);
	
	//Update All Interactables
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Set Save Data")
	void UpdateAllInteractables();

	//Clear Save
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Set Save Data")
	void ClearSave(bool ClearSeed);

	//Update All Resources
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Update Resources")
	void UpdateAllResources(const TMap<E_ResourceType, int32> & Resources);
	
	//Load Level
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Load Level")
	void LoadLevel();

};
