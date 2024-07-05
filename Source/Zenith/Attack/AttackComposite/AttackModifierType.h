#pragma once
//
// enum class EAttackModifier
// {
// 	//Normal Attack
// 	Flat_Damage,
// 	Percentage_Damage,
// 	//Attack Speed
// 	Attack_Speed,
// 	//Attack Movement Speed
// 	Movement_Speed,
// 	//OffCenterDistance
// 	OffCenterDistance,
// 	//Cluster Size
// 	Cluster_Size,
// 	//Number of Projectiles
// 	Number_Of_Projectiles,
// 	//Piercing
// 	Piercing,
// 	//Damage Area
// 	Damage_Area,
// 	None
// };

//unreal enum
UENUM(BlueprintType)
enum class EAttackModifier : uint8
{
	//Normal Attack
	Flat_Damage UMETA(DisplayName = "Flat Damage"),
	Percentage_Damage UMETA(DisplayName = "Percentage Damage"),
	//Attack Speed
	Attack_Speed UMETA(DisplayName = "Attack Speed"),
	//Attack Movement Speed
	Movement_Speed UMETA(DisplayName = "Movement Speed"),
	//OffCenterDistance
	OffCenterDistance UMETA(DisplayName = "Off Center Distance"),
	//Cluster Size
	Cluster_Size UMETA(DisplayName = "Cluster Size"),
	//Number of Projectiles
	Number_Of_Projectiles UMETA(DisplayName = "Number of Projectiles"),
	//Piercing
	Piercing UMETA(DisplayName = "Piercing"),
	//Damage Area
	Damage_Area		UMETA(DisplayName = "Damage Area"), 
	None UMETA(DisplayName = "None")
};
