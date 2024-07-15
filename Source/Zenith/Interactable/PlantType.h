#pragma once

//unreal enum
UENUM(BlueprintType)
enum class EPlantType : uint8
{
	MagicPower, //Colour and Magic effect -> essentially more damage?
	Health, //Enhance player constitution
	Momentum, //overall movement speed
	Mysterious,
	None,
};