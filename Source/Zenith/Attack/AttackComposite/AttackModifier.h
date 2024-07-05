#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Zenith/Attack/AttackComposite/Modifier.h"
#include "AttackModifier.generated.h"

USTRUCT(BlueprintType)
struct ZENITH_API FAttackModifier : public FTableRowBase
{
	GENERATED_BODY()
	//Item Name
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FName ItemName = "Item";

	//UI Icon with soft reference
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	TSoftObjectPtr<UTexture2D> UIIcon;
	
	//Modifiers Array
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Modifier")
	TArray<FModifier> Modifiers;

	//Description
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FString Description = "Item Description";
};
