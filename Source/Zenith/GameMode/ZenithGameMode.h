// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyHandle/GameMonsterHandle.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeUIHandle/PlayerUIHandle.h"
#include "GameModeUIHandle/ResourcesHandle.h"
#include "Zenith/Attack/AttackComposite/AttackModifier.h"
#include "Zenith/Interactable/PlantEffect.h"
#include "Zenith/Inventory/Resource.h"
#include "Zenith/ZenithPawn/Enemy/MonsterAttribute.h"
#include "ZenithGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ZENITH_API AZenithGameMode : public AGameModeBase, public IPlayerUIHandle, public IResourcesHandle, public IGameMonsterHandle
{
	GENERATED_BODY()

	//Player Experience
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	int32 PlayerExperience = 0;

	//Player Level
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	int32 PlayerLevel = 1;
	
	//Experience Table
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player", meta = (AllowPrivateAccess = "true"))
	TArray<int32> ExperienceTable;
	
protected:
	//Spawn Volumes
	UPROPERTY(BlueprintReadOnly, Category = "Spawn")
	TArray<class ASpawnVolume *> SpawnVolumes;

	//Resources
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Resources")
	TMap<E_ResourceType, int32> Resources;

	/*--------------------------------Tables----------------------------------
								  Assign in game
	----------------------------------Tables--------------------------------*/
#pragma region Tables
	//Attack Table
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="My Category")
	const UDataTable* AttackPropertyTable;

	//Player Experience Table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="My Category")
	const UDataTable* PlayerExperienceTable;

	//Monster table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="My Category")
	const UDataTable* MonsterTable;

	//Attack Modifier table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="My Category")
	const UDataTable* AttackModifierTable;

private:
	//Load Experience table
	void LoadExperienceTable();
#pragma endregion
public:
	//constructor
	AZenithGameMode();
	//Begin Play
	virtual void BeginPlay() override;
	//--------------------------------Game Time Events--------------------------------
#pragma region Game Time Events
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent")
	void OnDawnEvent();
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent")
	void OnMorningEvent();
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent")
	void OnNoonEvent();
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent")
	void OnDuskEvent();
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent")
	void OnNightEvent();
	UFUNCTION(BlueprintNativeEvent, Category = "GameEvent")
	void OnMidnightEvent();
#pragma endregion
	//--------------------------------Game Management--------------------------------
#pragma region Game Setup
	/**
	 * This function manages the Monster Spawning
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Management")
	void SpawnMonsters();

	/**
	 * Get Random Spawn Location
	 * @return 
	 */
	UFUNCTION(BlueprintCallable, Category = "Game Management")
	bool GetRandomSpawnLocation(FVector & SpawnLocation) const;
	
	UFUNCTION(BlueprintCallable, Category = "Game Management")
	FMonsterAttribute GetMonsterToSpawn() const;
#pragma endregion
	
#pragma region Game Management
	// add spawn volume
	void AddSpawnVolume(class ASpawnVolume * SpawnVolume);
#pragma endregion
	//--------------------------------Player Event Management--------------------------------
#pragma region Player Triggered Event Management
	//Start Game
private:
	//Player Controlled to start the game
	void StartGame() const;
	void LoadPlayerSkill(int32 SelectedCharacter) const;

#pragma endregion
	//--------------------------------Player Resource & EXP Management--------------------------------
#pragma region Player Resource Management
	//Update UI Resources
	virtual int32 GetResource_Implementation(const E_ResourceType ResourceType) override;
	virtual void GetResourceValid_Implementation(const E_ResourceType ResourceType, int32 & Amount, bool & bValid) override;
	virtual void GetResources_Implementation(TMap<E_ResourceType, int32> & PlayerResources) override;
	virtual void AddResource_Implementation(const E_ResourceType ResourceType, const int32 Amount) override;
	virtual void RemoveResource_Implementation(const E_ResourceType ResourceType, const int32 Amount) override;


#pragma region Resource Change Event
private:
	//Resource Change Event
    DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnResourceChange, E_ResourceType, ResourceType, int32, Amount);
public:
	UPROPERTY(BlueprintAssignable, Category="Resource Events")
	FOnResourceChange OnResourceChange;

	//Handle Update Resource
	void SaveResources() const;
	void HandleUpdateResource(const E_ResourceType ResourceType, const int32 Amount) const;
	
#pragma endregion
#pragma region Experience Change Event
private:
	//Experience Change Event
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnExperienceChange, float, Percentage, int32, Amount);
	UPROPERTY(BlueprintAssignable, Category="Experience Events")
	FOnExperienceChange OnExperienceChange;

	/**
	 * Update When Adding Experience
	 */
	void UpdatePlayerExperience() const;
	/**
	 * UI Method - included in @UpdatePlayerExperience();
	 * @param Percentage 
	 * @param Level 
	 */
	void HandleUpdateExperience(const float Percentage, const int32 Level) const;
	void OnLevelUp() const;
#pragma endregion
	
#pragma endregion
	//--------------------------------Player UI Management--------------------------------
#pragma region Player UI Management (Passive UI)
public:
	//Update UI Health
	UFUNCTION(BlueprintNativeEvent, Category = "Player State")
	void OnUpdateUIHealth();
	//Update UI Experience
	
	//Update UI Health
	virtual void UpdateHealth() override;

	//Pop Level UP UI
	UFUNCTION(BlueprintNativeEvent, Category = "Player State")
	void OnLevelUp();

protected:
	//Buff that can be selected for this round
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Buff", meta = (AllowPrivateAccess = "true"))
	TArray<FAttackModifier> BuffsToSelect;

	//Generate buffs to select
	UFUNCTION(BlueprintCallable, Category = "Buff")
	TArray<FAttackModifier> GenerateBuffsToSelect(int32 BuffNumber) const;

	//Check If Selected buff is valid
	UFUNCTION(BlueprintCallable,BlueprintPure, Category = "Buff")
	FAttackModifier CheckBuff(TArray<FAttackModifier> Buffs, FName Selected, bool & Success);
#pragma endregion

#pragma region Player UI Management (Player Input)
	//Select Tree
	UFUNCTION(BlueprintCallable, Category = "Tree")
	void SelectCharacter(int32 Selected);

	//Select Buff Option
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void SelectBuff(FName Selected);

	//buff selected
	UFUNCTION(BlueprintNativeEvent, Category = "Buff")
	void OnBuffSelected(FName Selected);

	//Add Buff to Player
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void AddBuffToPlayer(FAttackModifier Buff);
#pragma endregion
	
	/*--------------------------------Monster Triggered Events--------------------------------*/
#pragma region Monster Events
	//Monster Die
	virtual void OnMonsterKilled(const FName& MonsterName) override;

	//Player Experience
	void AddExperience(const int32 Amount);

	//Add Monster Drops to Player
	void AddMonsterDrops(E_ResourceType Type, int32 Amount);
#pragma endregion
	/*----------------------------------Plant Triggered Events--------------------------------*/

	UFUNCTION(BlueprintCallable, Category = "Plant")
	virtual void HarvestPlant(FPlantEffect PlantEffect);
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Plant")
	void OnPlantHarvested(FPlantEffect PlantEffect);
};


