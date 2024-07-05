#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LootEffect.h"
#include "LootItem.generated.h"


USTRUCT(BlueprintType)
struct ZENITH_API FLootItem : public FTableRowBase
{
	GENERATED_BODY()
	//Loot Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FName LootName = "Loot";

	//Mesh Class
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	UStaticMesh* Mesh;
	
	//Loot effects
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	TArray<FLootEffect> LootEffects;

	//Enhance Description
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	FString EnhanceDescription = "Increase Health by 5";
};
