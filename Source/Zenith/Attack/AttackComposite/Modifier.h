#pragma once

#include "CoreMinimal.h"
#include "AttackModifierType.h"
#include "GameFramework/Actor.h"
#include "Modifier.generated.h"

USTRUCT(BlueprintType)
struct ZENITH_API FModifier
{
	GENERATED_BODY()
	//Modifier Type
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifier")
	EAttackModifier ModifierName = EAttackModifier::None;

	//Amount
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifier")
	float Amount = 1.f;
};
