#pragma once

//unreal enum
UENUM(BlueprintType)
enum class EPlantType : uint8
{
	MagicPower, //Colour and Magic effect -> essentially more damage?
	SpeedPower, //Enhance player constitution
	ManaPower, //overall movement speed
	PhysiquePower, //Health
	MysteriousPower //Special Power,
};