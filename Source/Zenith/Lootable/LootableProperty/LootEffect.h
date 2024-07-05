#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectType.h"
#include "LootEffect.generated.h"


USTRUCT(BlueprintType)
struct ZENITH_API FLootEffect
{
	GENERATED_BODY()

	//Enhance Type
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	EEffectType EffectType = EEffectType::IncreaseHealth;

	//Enhance Amount
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Loot")
	float Amount = 5.f;
};
