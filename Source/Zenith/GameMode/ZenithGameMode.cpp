// Fill out your copyright notice in the Description page of Project Settings.


#include "ZenithGameMode.h"

#include "DataTables/PlayerLevel.h"
#include "GameFramework/GameStateBase.h"
#include "GameInstanceHandle/GameInstanceHandle.h"
#include "Zenith/Interactable/PlantPower.h"
#include "Zenith/SpawnVolume/SpawnVolume.h"
#include "Zenith/ZenithPawn/Character/ZenithCharacter.h"
#include "Zenith/ZenithPawn/Enemy/Enemy.h"
#include "Zenith/ZenithPawn/Enemy/MonsterAttribute.h"


AZenithGameMode::AZenithGameMode()
{
}

void AZenithGameMode::BeginPlay()
{
	Super::BeginPlay();
	LoadExperienceTable();
	LoadPlantPowerTable();
}

void AZenithGameMode::OnDawnEvent_Implementation()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dawn Event"));
	}
}

void AZenithGameMode::OnMorningEvent_Implementation()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Morning Event"));
	}
}

void AZenithGameMode::OnNoonEvent_Implementation()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Noon Event"));
	}
}

void AZenithGameMode::OnDuskEvent_Implementation()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Dusk Event"));
	}
}

void AZenithGameMode::OnNightEvent_Implementation()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Night Event"));
	}
}

void AZenithGameMode::OnMidnightEvent_Implementation()
{
	if(GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Midnight Event"));
	}
}

void AZenithGameMode::LoadExperienceTable()
{
	if(PlayerExperienceTable)
	{
		TArray<FPlayerLevel*> LocalLevels;
		PlayerExperienceTable->GetAllRows<FPlayerLevel>("", LocalLevels);
		for(const FPlayerLevel* PLevel : LocalLevels)
		{
			ExperienceTable.Add(PLevel->Experience);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerExperienceTable is not initialized."));
	}
}


void AZenithGameMode::SpawnMonsters(const int NumberOfMonsters)
{
	//Number of Monsters to Spawn
	FMonsterAttribute MonsterToSpawn = GetMonsterToSpawn();
	//Types of Monsters to Spawn
	for(int i = 0; i < NumberOfMonsters; i++)
	{
		//Get Random Volume
		const int32 RandomIndex = FMath::RandRange(0, SpawnVolumes.Num() - 1);
		//Spawn Monster
		if(ASpawnVolume* SpawnVolume = SpawnVolumes[RandomIndex])
		{
			//Spawn Monster
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AEnemy * Monster = GetWorld()->SpawnActor<AEnemy>(MonsterToSpawn.BlueprintClass,
				SpawnVolume->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
			Monster->InitializeEnemy(MonsterToSpawn);
		}
	}
}

bool AZenithGameMode::GetRandomSpawnLocation(FVector& SpawnLocation) const
{
	const int32 RandomIndex = FMath::RandRange(0, SpawnVolumes.Num() - 1);
	if(const ASpawnVolume* SpawnVolume = SpawnVolumes[RandomIndex])
	{
		SpawnLocation = SpawnVolume->GetActorLocation();
		return true;
	}
	return false;
}

FMonsterAttribute AZenithGameMode::GetMonsterToSpawn() const
{
	// Check if the MonsterTable is valid
	if (!MonsterTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("MonsterTable is not initialized."));
		return FMonsterAttribute(); 
	}

	TArray<FName> RowNames = MonsterTable->GetRowNames();

	if (RowNames.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("MonsterTable is empty."));
		return FMonsterAttribute(); 
	}

	FMonsterAttribute* MonsterData = MonsterTable->FindRow<FMonsterAttribute>(RowNames[0], "");
	if (!MonsterData)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to find MonsterData."));
		return FMonsterAttribute();
	}
	
	// Return the found MonsterData by value (ensure MonsterData is not nullptr before dereferencing)
	return *MonsterData;
}



void AZenithGameMode::AddSpawnVolume(ASpawnVolume* SpawnVolume)
{
	if(SpawnVolume)
	{
		SpawnVolumes.Add(SpawnVolume);
	}
}

void AZenithGameMode::StartGame() const
{
	//Enable State Tick
	GetWorld()->GetGameState()->SetActorTickEnabled(true);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Game Started"));
	//Cast Spell
}

void AZenithGameMode::LoadPlayerSkill(int32 Selected)
{
	//cast to character
	if(AZenithCharacter * PlayerCharacter = Cast<AZenithCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		if(AttackPropertyTable)
		{
			if(const auto Data = AttackPropertyTable->FindRow<FAttackProperty>("DefaultAttack", ""))
			{
				PlayerAttackComponent = PlayerCharacter->LoadSkill(Data);
			}
		}
		//load skill
	}
}

TArray<FAttackModifier> AZenithGameMode::GenerateBuffsToSelect(int32 BuffNumber) const
{
	//three random buffs from attack modifier table
	TArray<FAttackModifier> Buffs;
	if(AttackModifierTable)
	{
		TArray<FAttackModifier*> LocalModifiers;
		AttackModifierTable->GetAllRows<FAttackModifier>("", LocalModifiers);
		//generate 3 unique random numbers within the table
		//get table length
		const int32 TableLength = LocalModifiers.Num();
		TArray<int32> RandomNumbers;
		const int32 BuffToGenerate = BuffNumber <= TableLength ? BuffNumber : TableLength;
		while(RandomNumbers.Num() < BuffNumber)
		{
			RandomNumbers.AddUnique(FMath::RandRange(0, TableLength - 1));
		}
		//get the buff
		for(int32 i = 0; i < BuffToGenerate; i++)
		{
			Buffs.Add(*LocalModifiers[RandomNumbers[i]]);
		}
	}
	return Buffs;
}

FAttackModifier AZenithGameMode::CheckBuff(TArray<FAttackModifier> Buffs, FName Selected, bool & Success)
{
	for(const FAttackModifier& CurrBuff : Buffs)
	{
		if(CurrBuff.ItemName == Selected)
		{
			Success = true;
			return CurrBuff;
		}
	}
	Success = false;
	return FAttackModifier();
}
void AZenithGameMode::SelectCharacter(int32 Selected)
{
	if(GEngine)
	{
		LoadPlayerSkill(Selected);
		StartGame();
	}
}

void AZenithGameMode::SelectBuff(FName Selected)
{
	//on buff selected
	OnBuffSelected(Selected);
}

void AZenithGameMode::OnBuffSelected_Implementation(FName Selected)
{
}

void AZenithGameMode::AddBuffToPlayer(FAttackModifier Buff)
{
	if(AZenithCharacter * PlayerCharacter = Cast<AZenithCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		FAttackModifier * Copy = new FAttackModifier(Buff);
		PlayerCharacter->AddAttackModifier(Copy);
	}
}

void AZenithGameMode::OnMonsterKilled(const FName& MonsterName)
{
	//Get Monster Data
	if(FMonsterAttribute* MonsterData = MonsterTable->FindRow<FMonsterAttribute>(MonsterName, ""))
	{
		AddExperience(MonsterData->Experience);
		
		for(const auto& Pair : MonsterData->Loot)
		{
			AddMonsterDrops(Pair.Key, Pair.Value);
		}
	}
}

void AZenithGameMode::SaveResources() const
{
	if(GetGameInstance())
		if (UObject* InterfacePointer = Cast<UObject>(GetGameInstance()))
		{
			IGameInstanceHandle::Execute_UpdateAllResources(InterfacePointer, Resources);
		}
}

void AZenithGameMode::HandleUpdateResource(const E_ResourceType ResourceType, const int32 Amount) const
{
	SaveResources();
	OnResourceChange.Broadcast(ResourceType, Amount);
}

void AZenithGameMode::UpdatePlayerExperience() const
{
	//Save Game
	if(GetGameInstance())
		if (UObject* InterfacePointer = Cast<UObject>(GetGameInstance()))
		{
			IGameInstanceHandle::Execute_UpdatePlayerExperience(InterfacePointer, PlayerExperience, PlayerLevel);
		}
	//Update UI
	HandleUpdateExperience((float)PlayerExperience/ExperienceTable[PlayerLevel], PlayerLevel);
}

void AZenithGameMode::HandleUpdateExperience(const float Percentage, const int32 Level) const
{
	OnExperienceChange.Broadcast(Percentage, Level);
}

void AZenithGameMode::OnLevelUp() const
{
	
}

void AZenithGameMode::UpdateHealth()
{
	OnUpdateUIHealth();
}

void AZenithGameMode::OnLevelUp_Implementation()
{
}

int32 AZenithGameMode::GetResource_Implementation(const E_ResourceType ResourceType)
{
	if(const int32* FoundResource = Resources.Find(ResourceType))
	{
		return *FoundResource;
	}
	return 0;
}

void AZenithGameMode::GetResourceValid_Implementation(const E_ResourceType ResourceType, int32& Amount, bool& bValid)
{
	if(const int32* FoundResource = Resources.Find(ResourceType))
	{
		Amount = *FoundResource;
		bValid = true;
	}
	else
	{
		Amount = 0;
		bValid = false;
	}
}

void AZenithGameMode::GetResources_Implementation(TMap<E_ResourceType, int32>& PlayerResources)
{
	PlayerResources = Resources;
}

void AZenithGameMode::AddResource_Implementation(const E_ResourceType ResourceType, const int32 Amount)
{
	if(int32 * FoundResource = Resources.Find(ResourceType))
	{
		*FoundResource += Amount;
		HandleUpdateResource(ResourceType, *FoundResource);
	}
	else
	{
		Resources.Add(ResourceType, Amount);
		HandleUpdateResource(ResourceType, Amount);
	}
}

void AZenithGameMode::RemoveResource_Implementation(const E_ResourceType ResourceType, const int32 Amount)
{
	//Assume the request is prechecked
	if(int32* FoundResource = Resources.Find(ResourceType))
	{
		*FoundResource -= Amount;
		HandleUpdateResource(ResourceType, *FoundResource);
	}
	else
	{
		if(GEngine)
		{
			//Error Message
			//Solution, check the resources to be valid before removing
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red,
				TEXT(
					"Game Mode Remove Resources not valid"));
		}
	}
}

void AZenithGameMode::AddExperience(const int32 Amount)
{
	PlayerExperience += Amount;
	int32 CurrLeveCap = ExperienceTable[PlayerLevel];
	if(PlayerExperience >= CurrLeveCap)
	{
		PlayerLevel++;
		PlayerExperience = 0;
		CurrLeveCap = ExperienceTable[PlayerLevel];
		OnLevelUp();
		
	}
	if(CurrLeveCap != 0)
		UpdatePlayerExperience();
}

void AZenithGameMode::AddMonsterDrops(const E_ResourceType Type, const int32 Amount)
{
	//debug message
	AddResource_Implementation(Type, Amount);
}

void AZenithGameMode::AddMapDrop(const E_ResourceType Type, const int32 Amount)
{
	AddResource_Implementation(Type, Amount);
}

void AZenithGameMode::HarvestPlant(FPlantEffect PlantEffect)
{
	OnPlantHarvested(PlantEffect);
	if(Player == nullptr)
	{
		Player = Cast<AZenithCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}
	if(Player)
	{
		switch (PlantEffect.PlantType)
		{
			case EPlantType::MagicPower:
				Player->AddMagicPowerPoint(GetPlantPower(PlantEffect));
				break;
			case EPlantType::SpeedPower:
				Player->AddSpeedPowerPoint(GetPlantPower(PlantEffect));
				break;
			case EPlantType::PhysiquePower:
				Player->AddPhysiquePowerPoint(GetPlantPower(PlantEffect));
				break;
			case EPlantType::ManaPower:
				Player->AddManaPowerPoint(GetPlantPower(PlantEffect));
				break;
			case EPlantType::MysteriousPower:
				break;
		}
	}
	
}

float AZenithGameMode::GetPlantPower(FPlantEffect PlantEffect) const
{
	//The data should be store in a table, so it can be modified easily.
	return PlantEffect.Amount;
}

void AZenithGameMode::LoadPlantPowerTable()
{
	if(PlantPowerTable)
	{
		TArray<FPlantPower*> LocalLevels;
		PlantPowerTable->GetAllRows<FPlantPower>("", LocalLevels);
		for(const FPlantPower* PLevel : LocalLevels)
		{
			PlantPowerTableData.Add(PLevel->Amount);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlantPowerTable is not initialized."));
	}
}

void AZenithGameMode::OnUpdateUIHealth_Implementation()
{
	
}

