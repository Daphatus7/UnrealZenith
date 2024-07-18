#pragma once

#include "CoreMinimal.h"
#include "PlantType.h"
#include "PlantEffect.generated.h"

USTRUCT(BlueprintType)
struct ZENITH_API FPlantEffect : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plant")
	EPlantType PlantType = EPlantType::ManaPower;

	//Level
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plant")
	int32 Level = 1;

	//Amount
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plant")
	float Amount = 1.0f;
};
