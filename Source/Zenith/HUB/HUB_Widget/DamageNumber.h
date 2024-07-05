#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "DamageNumber.generated.h"

UCLASS()
class ZENITH_API UDamageNumber : public UUserWidget
{
	GENERATED_BODY()

protected:
	// Damage text widget
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageText;

public:
	UDamageNumber(const FObjectInitializer& ObjectInitializer);

	// Function to set the damage number
	UFUNCTION(BlueprintCallable, Category="Damage")
	virtual void SetDamageNumber(float Damage);
};
