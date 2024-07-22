#pragma once

enum class EResourceType
{
	Star,
	Moon,
	Sun,
	Gold
};

//unreal enum
UENUM(BlueprintType)
enum class E_ResourceType : uint8
{
	Star,
	Moon,
	Sun,
	Gold
};