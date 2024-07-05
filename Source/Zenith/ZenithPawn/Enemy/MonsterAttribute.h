#pragma once

#include "CoreMinimal.h"
#include "Zenith/Inventory/Resource.h"
#include "MonsterAttribute.generated.h"

USTRUCT(BlueprintType)
struct ZENITH_API FMonsterAttribute : public FTableRowBase
{
	GENERATED_BODY()
	/*-----------------Data----------------------------------Data-----------------*/
	//Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	FName Name = "Piggy";

	//Health
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	float Health = 100.f;
	float HealthMax = 100.f;
	//Damage
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	float Damage = 1.0f;
	
	//Movement Speed
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	float MovementSpeed = 300.f;
	
	//EXP
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	int32 Experience = 1;
	
	//LEVEL
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Data")
	int32 Level = 1;

	/*----------------------------Base Class------------------------------------------*/
	//Blueprint Class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	TSubclassOf<class AEnemy> BlueprintClass;

	
	/*-----------------Visual----------------------------------Visual-----------------*/
	//Skeletal mesh
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Visual")
	TSoftObjectPtr<USkeletalMesh> SkeletalMesh;

	/*-----------------loot----------------------------------loot-----------------*/
	//Loot
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	TMap<E_ResourceType, int32> Loot;
};
