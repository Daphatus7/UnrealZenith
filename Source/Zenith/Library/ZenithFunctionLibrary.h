// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ZenithFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ZENITH_API UZenithFunctionLibrary : public UObject
{
	GENERATED_BODY()


public:
	//Simplified debug function
	UFUNCTION(BlueprintCallable, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static void DxPrint(const FString& Message, const bool Tick);

	//Extend Vector in the direction by length
	UFUNCTION(BlueprintCallable, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static FVector ExtendVector(const FVector& Vector, const float Length);

	//Get Screen Location to World Location
	UFUNCTION(BlueprintCallable, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static FVector GetMouseToWorldLocation(const APlayerController* PlayerController);

	//get direction vector
	UFUNCTION(BlueprintPure, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static FVector GetDirectionVector(const FVector& Start, const FVector& End);

	//get position of length x in the direction of vector
	UFUNCTION(BlueprintPure, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static FVector GetPositionInDirection(const FVector& Start, const FVector& Direction, const float Length);

	//get fixed length screen projection location
	UFUNCTION(BlueprintPure, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static FVector GetFixedLengthScreenProjectionLocation(const APlayerController* PlayerController, const float Length);

	//project 3D vector to xy plane
	UFUNCTION(BlueprintPure, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static FVector2D ProjectVectorToXYPlane(const FVector& Vector);
	//EnumToString
	UFUNCTION(BlueprintPure, Category = "Zenith Function Library", meta = (Keywords = "ZenithFunctionLibrary"))
	static FString EnumToString(const EAttackModifier EnumValue)
	{
		const UEnum* EnumPtr = StaticEnum<EAttackModifier>();
		if (!EnumPtr)
		{
			return FString("Invalid");
		}

		return EnumPtr->GetNameStringByValue((int64)EnumValue);
	}


};
