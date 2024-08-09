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
	//Flat Damage
	Flat_Damage UMETA(DisplayName = "Flat Damage"),

	//Damage increase percentage
	Damage_Increase_Percentage UMETA(DisplayName = "Damage Increase Percentage"),

	//Number of Projectiles
	Number_Of_Projectiles UMETA(DisplayName = "Number of Projectiles"),

	//Damage Area
	Damage_Area UMETA(DisplayName = "Damage Area"),

	//Movement Speed
	Movement_Speed UMETA(DisplayName = "Movement Speed"),

	//Number of Clusters
	Number_Of_Clusters UMETA(DisplayName = "Number of Clusters"),

	//Attack Speed
	Attack_Speed UMETA(DisplayName = "Attack Speed"),

	//Pierce Count
	Pierce_Count UMETA(DisplayName = "Pierce Count"),

	//Off-center Distance
	Off_Center_Distance UMETA(DisplayName = "Off Center Distance"),

	//Cluster Size
	Cluster_Size UMETA(DisplayName = "Cluster Size"),

	//Effect Enhanced
	Effect_Enhanced UMETA(DisplayName = "Effect Enhanced"),

	//Critical Strike Chance
	Critical_Strike_Chance UMETA(DisplayName = "Critical Strike Chance"),

	//None (default)
	None UMETA(DisplayName = "None")
};
