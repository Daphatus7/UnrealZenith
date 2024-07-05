// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameInstanceHandle/GameInstanceHandle.h"
#include "ZenithGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ZENITH_API UZenithGameInstance : public UGameInstance, public IGameInstanceHandle
{
	GENERATED_BODY()
	//Save Game
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "SaveGame", meta = (AllowPrivateAccess = "true"))
	class UZenithSaveGame* SaveGameRef;
public:
	/*-------------------SaveLoadHandle-------------------*/

	//Update All Resources
	//virtual void UpdateAllResources_Implementation(const TMap<E_ResourceType, int32> & Resources) override;
};
