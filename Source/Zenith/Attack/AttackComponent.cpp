// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "Zenith/Attack/AttackProperty.h"
#include "Zenith/Library/ZenithFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

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
	//Get Cluster Remainings
	const int32 RemainingAttacks = AttackCluster->GetRemainingClusterSize();
	const int32 InactiveAttacks = AttackCluster->GetInactiveClusterSize();
	

	//the number of instances can spawn
	const int32 TotalAttacks = RemainingAttacks + InactiveAttacks;
	int32 NumberOfInstance = TotalAttacks < AttackProperty.NumberOfProjectiles ?
								TotalAttacks : AttackProperty.NumberOfProjectiles;
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
		NewAttack->InitializeParent(reinterpret_cast<IAttackClusterHandle*>(AttackCluster));
		AttackCluster->RegisterAttack(NewAttack);
		NewAttack->InitializeProperty(AttackProperty.Damage,
								AttackProperty.bPiercing,
								AttackProperty.DamageArea,
								AttackProperty.FX);
	}
	return true;
}

void UAttackComponent::AssignAttackType(FAttackProperty AttackType)
{
	AttackProperty = AttackType;
	InitializeCluster();
}


//-------------------------------------Attack Modification--------------------------------------------------//

void UAttackComponent::UpdateCluster()
{
	AttackCluster->UpdateCluster(AttackProperty.MovementSpeed, AttackProperty.OffCenterDistance, AttackProperty.ClusterSize);
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
	AttackProperty.MovementSpeed,
	AttackProperty.OffCenterDistance,
	AttackProperty.ClusterSize);
}

void UAttackComponent::IncreaseDamage(float FlatDamage)
{
	AttackProperty.Damage += FlatDamage;
}

void UAttackComponent::IncreaseDamagePercentage(float Percentage)
{
	AttackProperty.Damage *= Percentage;
}

void UAttackComponent::IncreaseAttackSpeed(float Percentage)
{
	AttackProperty.AttackSpeed *= Percentage;
}

void UAttackComponent::IncreaseNumberOfProjectiles(int32 NumberOfProjectiles)
{
	AttackProperty.NumberOfProjectiles += NumberOfProjectiles;
}

void UAttackComponent::IncreaseDamageArea(float DamageArea)
{
	AttackProperty.DamageArea += DamageArea;
}

void UAttackComponent::IncreaseMovementSpeed(float MovementSpeed)
{
	AttackProperty.MovementSpeed += MovementSpeed;
}


void UAttackComponent::IncreaseClusterSize(int32 ClusterSize)
{
	AttackProperty.ClusterSize += ClusterSize;
}

void UAttackComponent::AddAttackModifier(FAttackModifier * Modifier)
{
	AttackModifiers.Add(Modifier);
	//recalculate the attack property
	ApplyModifer();
}

void UAttackComponent::RemoveAttackModifier(FAttackModifier * Modifier)
{
	if(AttackModifiers.Contains(Modifier))
	{
		AttackModifiers.RemoveSingle(Modifier);
	}
}

void UAttackComponent::ApplyModifer()
{

	//Reset the attack property
	AttackProperty = AttackPropertyDefault;
	//printout the length of the attack modifiers
	UE_LOG(LogTemp, Warning, TEXT("Attack Modifiers Length: %d"), AttackModifiers.Num());
	for(FAttackModifier * AttackModifier: AttackModifiers)
	{
		UE_LOG(LogTemp, Warning, TEXT("Attack Modifier: %s"), *AttackModifier->ItemName.ToString());
		for(FModifier Modifier: AttackModifier->Modifiers)
		{
			//print out the modifier name
			UE_LOG(LogTemp, Warning, TEXT("Modifier Name: %s Increase Amount %f"),
				*UZenithFunctionLibrary::EnumToString(Modifier.ModifierName), Modifier.Amount);
			switch (Modifier.ModifierName)
			{
			case EAttackModifier::Flat_Damage:
				IncreaseDamage(Modifier.Amount);
				break;
			case EAttackModifier::Percentage_Damage:
				AttackProperty.Damage *= Modifier.Amount;
				break;
			case EAttackModifier::Attack_Speed:
				AttackProperty.AttackSpeed += Modifier.Amount;
				break;
			case EAttackModifier::Movement_Speed:
				AttackProperty.MovementSpeed += Modifier.Amount;
				break;
			case EAttackModifier::OffCenterDistance:
				AttackProperty.OffCenterDistance += Modifier.Amount;
				break;
			case EAttackModifier::Cluster_Size:
				AttackProperty.ClusterSize += Modifier.Amount;
				break;
			case EAttackModifier::Number_Of_Projectiles:
				AttackProperty.NumberOfProjectiles += Modifier.Amount;
				break;
			case EAttackModifier::Piercing:
				AttackProperty.bPiercing = true;
				break;
			case EAttackModifier::Damage_Area:
				AttackProperty.DamageArea += Modifier.Amount;
				UE_LOG(LogTemp, Warning, TEXT("Damage Area: %f"), AttackProperty.DamageArea);
				break;
			case EAttackModifier::None:
				break;
			default: ;
			}
		}
	}
	//Update the cluster
	ReinitializeAttackProperty();
}

void UAttackComponent::ReinitializeAttackProperty()
{
	//Modified Attack Property
	UE_LOG(LogTemp, Warning, TEXT("Modified Attack Property Damage %f Piercing %d Damage Area %f Movement Speed %f Off Center Distance %f Cluster Size %d"),
		AttackProperty.Damage, AttackProperty.bPiercing, AttackProperty.DamageArea, AttackProperty.MovementSpeed, AttackProperty.OffCenterDistance, AttackProperty.ClusterSize);
	AttackCluster->UpdateCluster(AttackProperty.MovementSpeed,
		AttackProperty.OffCenterDistance,
		AttackProperty.ClusterSize);
	AttackCluster->ReinitializeAttack(AttackProperty.Damage,
		AttackProperty.bPiercing,
		AttackProperty.DamageArea);
}
