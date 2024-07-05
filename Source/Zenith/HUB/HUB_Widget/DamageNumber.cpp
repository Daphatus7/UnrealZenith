#include "DamageNumber.h"

UDamageNumber::UDamageNumber(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer), DamageText(nullptr)
{
	// Constructor code here
}

void UDamageNumber::SetDamageNumber(float Damage)
{
	if (DamageText)
	{
		// Format the damage number as a string with desired formatting
		DamageText->SetText(FText::AsNumber(FMath::RoundToInt(Damage)));
	}
}
