// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"

#include "AttackAttribute/AttackAttribute.h"
#include "AttackMath/AttackMath.h"
#include "Zenith/Attack/AttackProperty.h"
#include "Zenith/Library/ZenithFunctionLibrary.h"
#include "Zenith/ZenithPawn/Character/ZenithCharacter.h"

UAttackComponent::UAttackComponent()
{
	//Enable tick
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(AttackCluster)
	AttackCluster->DebugClusterMessage();
}

bool UAttackComponent::Attack(const FVector& Direction)
{
	if(!AttackCluster) return false;
	//Create Cluster to store attacks
	//Get Cluster Remaining Attacks
	const int32 RemainingAttacks = AttackCluster->GetRemainingClusterSize();
	const int32 InactiveAttacks = AttackCluster->GetInactiveClusterSize();
	

	//the number of instances can spawn
	const int32 TotalAttacks = RemainingAttacks + InactiveAttacks;
	int32 NumberOfInstance = TotalAttacks < AttackProperty.AttackData.NumberOfProjectiles ?
								TotalAttacks : AttackProperty.AttackData.NumberOfProjectiles;
	UE_LOG(LogTemp, Warning, TEXT("Total Attacks: %d Inactive Attacks: %d Remaining Attacks: %d"), TotalAttacks, InactiveAttacks, RemainingAttacks);
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = AttackCluster;
	//Get how many can be allocated to the cluster
	//Initialize Cluster Property
	//Can Spawn More
	if(NumberOfInstance <= 0)
	{
		return false;
	}
	for(int i = 0; i < InactiveAttacks && NumberOfInstance > 0; i++, NumberOfInstance--)
	{
		AttackCluster->ActivateAttack();
	}
	
	//Spawn new ones if possible
	for(int j = 0; j < RemainingAttacks && NumberOfInstance > 0; j++, NumberOfInstance--)
	{
		AAttack* NewAttack = GetWorld()->SpawnActor<AAttack>(
							AttackProperty.ClassToSpawn,
							GetOwner()->GetActorLocation(),
							GetOwner()->GetActorRotation(), SpawnParams);
		if(NewAttack == nullptr)
		{
			if(GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack is not valid"));
			}
					
		}
		NewAttack->InitializeParent(AttackCluster);
		AttackCluster->RegisterAttack(NewAttack);
		NewAttack->InitializeProperty(AttackProperty.AttackData);
	}
	return true;
}

void UAttackComponent::AssignAttackType(FAttackProperty AttackType)
{
	AttackProperty = AttackType;
	InitializeCluster();
}


//-------------------------------------Attack Modification--------------------------------------------------//

float UAttackComponent::GetAttackLevelExperience(int32 Level)
{
	//data not loaded
	if (AttackLevelData.Num() == 0)
	{
		LoadAttackLevelData();
		if(AttackLevelData.Num() == 0)
		{
			//return maximum float number
			return TNumericLimits<float>::Max()/2;
		}
	}
	//Data has loaded and valid index
	if (AttackLevelData.IsValidIndex(Level - 1))
	{
		return AttackLevelData[Level - 1];
	}
	
	//return max value if the level is out of range
	return AttackLevelData.Last();
}


float UAttackComponent::GetAttackSpeedCurveValue(int32 Level)
{
	//data not loaded
	if (AttackSpeedData.Num() == 0)
	{
		LoadAttackSpeedTable();
		if(AttackSpeedData.Num() == 0)
		{
			//return maximum float number
			return TNumericLimits<float>::Max()/2;
		}
	}
	//Data has loaded and valid index
	if (AttackSpeedData.IsValidIndex(Level - 1))
	{
		return AttackSpeedData[Level - 1];
	}
	
	//return max value if the level is out of range
	return AttackSpeedData.Last();
}

void UAttackComponent::LoadAttackSpeedTable()
{
	if(UZenithFunctionLibrary::LoadCurveTableData(AttackSpeedTable, "Curve", AttackSpeedData, TotalLevels * 10))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack Speed Data Not Loaded"));
	}
}

void UAttackComponent::LoadAttackLevelData()
{
	if(!UZenithFunctionLibrary::LoadCurveTableData(AttackLevelTable, "Curve", AttackLevelData, TotalLevels))
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack Level Data Not Loaded"));
	}
	// else
	// {
	// 	//print out the attack level data
	// 	for(float Data: AttackLevelData)
	// 	{
	// 		UE_LOG(LogTemp, Warning, TEXT("Attack Level Data: %f"), Data);
	// 	}
	// }
}

void UAttackComponent::UpdateCluster()
{
	AttackCluster->UpdateCluster(AttackProperty.AttackData.MovementSpeed,
		AttackProperty.AttackData.OffCenterDistance,
		AttackProperty.AttackData.ClusterSize);
}

void UAttackComponent::InitializeCluster()
{
	//Initialize Cluster
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	AttackCluster = GetWorld()->SpawnActor<AAttackGroup>(
						AttackProperty.ClusterToSpawn,
						GetOwner()->GetActorLocation(),
						GetOwner()->GetActorRotation(), SpawnParams);
	AttackCluster->InitializeCluster(
	AttackProperty.AttackData.MovementSpeed,
	AttackProperty.AttackData.OffCenterDistance,
	AttackProperty.AttackData.ClusterSize);
}

void UAttackComponent::AddAttackModifier(FModifier * Modifier)
{
	AttackModifiers.Add(Modifier);
	//recalculate the attack property
	ApplyModifer();
}

void UAttackComponent::RemoveAttackModifier(FModifier * Modifier)
{
	if(AttackModifiers.Contains(Modifier))
	{
		AttackModifiers.RemoveSingle(Modifier);
	}
}

void UAttackComponent::ApplyModifer()
{
	//AttackProperty.AttackData = UAttackComponent::GetNewAttackData(AttackPropertyDefault.AttackData, AttackModifiers);
	UE_LOG(LogTemp, Warning, TEXT("Apply Attack Modifer not implemented"), AttackProperty.AttackData.Damage);
	ReinitializeAttackProperty();
}

void UAttackComponent::ReinitializeAttackProperty()
{
	AttackCluster->UpdateCluster(AttackProperty.AttackData.MovementSpeed,
		AttackProperty.AttackData.OffCenterDistance,
		AttackProperty.AttackData.ClusterSize);
	AttackCluster->ReinitializeAttack(AttackProperty.AttackData);
}

void UAttackComponent::AddAttackAttribute(UAttackAttribute * AttackAttribute)
{
	/**
	 * if the attack attribute is not in the map, add it
	 */
	if(AttackAttribute == nullptr) return;
	if(AttackAttributes.Contains(AttackAttribute->GetAttackModifierType()))
	{
		AttackAttributes.FindRef(AttackAttribute->GetAttackModifierType())->LevelUp();
		// Assign Property
	}
	/**
	 * else level up the attack attribute
	 */
	else
	{
		AttackAttributes.Add(AttackAttribute->GetAttackModifierType(), AttackAttribute);
		AttackAttribute->AssignAttackDataHandle(this);
		AttackAttribute->AssignCluster(AttackCluster);
	}
}

void UAttackComponent::ApplyFlatDamage(float Amount)
{
	AttackProperty.AttackData.Damage = AttackPropertyDefault.AttackData.Damage + Amount;
	ReinitializeAttackProperty();

}

void UAttackComponent::ApplyDamageIncreasePercentage(float Amount)
{
	AttackProperty.AttackData.Damage = AttackPropertyDefault.AttackData.Damage * (1 + Amount);
	ReinitializeAttackProperty();

}

void UAttackComponent::ApplyNumberOfProjectiles(const int32 Amount)
{
	AttackProperty.AttackData.NumberOfProjectiles = AttackPropertyDefault.AttackData.NumberOfProjectiles + Amount;
	UE_LOG(LogTemp, Warning, TEXT("Number of Projectiles: %d"), AttackProperty.AttackData.NumberOfProjectiles);
	ReinitializeAttackProperty();

}

void UAttackComponent::ApplyDamageArea(const float Amount)
{
	AttackProperty.AttackData.DamageArea = AttackPropertyDefault.AttackData.DamageArea * (1 + Amount);
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyMovementSpeed(const float Amount)
{
	AttackProperty.AttackData.MovementSpeed = AttackPropertyDefault.AttackData.MovementSpeed * (Amount);
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyNumberOfClusters(const int32 Amount)
{
	AttackProperty.AttackData.NumberOfCluster = AttackPropertyDefault.AttackData.NumberOfCluster + Amount;
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyAttackSpeed(const float Amount)
{
	AttackProperty.AttackData.AttackSpeed = AttackPropertyDefault.AttackData.AttackSpeed * (Amount);
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyPierceCount(const int32 Amount)
{
	AttackProperty.AttackData.PierceCount = AttackPropertyDefault.AttackData.PierceCount + Amount;
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyOffCenterDistance(const float Amount)
{
	AttackProperty.AttackData.OffCenterDistance = AttackPropertyDefault.AttackData.OffCenterDistance + Amount;
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyClusterSize(const int32 Amount)
{
	AttackProperty.AttackData.ClusterSize = AttackPropertyDefault.AttackData.ClusterSize + Amount;
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyEffectEnhanced(const float Amount)
{
	AttackProperty.AttackData.EffectEnhanced = AttackPropertyDefault.AttackData.EffectEnhanced * ( 1 + Amount);
	ReinitializeAttackProperty();
}

void UAttackComponent::ApplyCriticalStrikeChance(const float Amount)
{
	AttackProperty.AttackData.CriticalStrikeChance = AttackPropertyDefault.AttackData.CriticalStrikeChance + Amount;
	ReinitializeAttackProperty();
}

