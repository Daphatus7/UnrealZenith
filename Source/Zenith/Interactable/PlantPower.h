#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlantPower.generated.h"


USTRUCT(BlueprintType)
struct ZENITH_API FPlantPower : public FTableRowBase
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Plant")
	float Amount = 1.0f;
};
