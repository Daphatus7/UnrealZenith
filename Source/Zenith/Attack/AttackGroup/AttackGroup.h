// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Zenith/Attack/AttackDecorator/Attack.h"
#include "AttackGroup.generated.h"

class AAttack;

UCLASS()
class ZENITH_API AAttackGroup : public AActor
{
	GENERATED_BODY()
	//Scene Component
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent * SceneComponent;

protected:
	//-----------------------------------Attacks to control-----------------------------------------
	//All the attacks in the cluster
	UPROPERTY(EditAnywhere, Category = "Attack Cluster")
	TArray<AAttack*> Attacks;
	
	//-----------------------------------Modifiable Properties --------------------------------------
	//Mesh - debug only
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent * Mesh;
	//Speed can be either spin or linear
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	float MovementSpeed = 1.0f;
	//Off center distance
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	float OffCenterDistance = 0.0f;
	//Cluster Size
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Damage, meta = (AllowPrivateAccess = "true"))
	int32 ClusterSize = 3;

	
	//-----------------------------------Administration ---------------------------------------------
	//Parent Attack Component


public:
	AAttackGroup();

	//begin play
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaTime) override;

	//-----------------------------------Compulsory Initializers--------------------------------------
	//1. Initialize the cluster
	virtual void InitializeCluster(const float InitMovementSpeed, const float InitOffCenterDistance, const
								   int32 InitClusterSize);
	//Update the movement each frame, has been added to the tick function
	virtual void UpdateMotion(float DeltaTime){}

	//-----------------------------------Cluster Getters ---------------------------------------------
	int32 GetRemainingClusterSize() const
	{
		return ClusterSize - Attacks.Num();
	}
	
	int32 GetInactiveClusterSize() const
	{
		int32 InactiveClusterSize = 0;
		for(AAttack * Attack : Attacks)
		{
			//check if the attack is active
			if(!Attack->IsAttackActive())
			{
				//Is active?
				InactiveClusterSize++;
			}
		}
		return InactiveClusterSize;
	}
	//-----------------------------------Administration ---------------------------------------------
	//Register Attack
	void RegisterAttack(AAttack * Attack)
	{
		Attacks.Add(Attack);
		InitializeAttack(Attack);
	}

	void ActivateAttack()
	{
		//Activate the first inactive attack
		for(AAttack * Attack : Attacks)
		{
			//printout the attack
			if(!Attack->IsAttackActive())
			{
				UE_LOG(LogTemp, Warning, TEXT("Activating Attack: %s"), *Attack->GetName());
				Attack->Activate();
				InitializeAttack(Attack);
				return;
			}
		}
	}
	// //Activate
	// virtual void Activate();
	// //Deactivate
	// virtual void Deactivate();

	//-----------------------------------Attack Control ---------------------------------------------
	//Move to initial Location
	virtual void InitializeAttack(AActor* Attack)
	{
		
	}

	virtual void UpdateCluster(const float NewMovementSpeed, const float NewOffCenterDistance, const int32 NewClusterSize)
	{
		MovementSpeed = NewMovementSpeed;
		OffCenterDistance = NewOffCenterDistance;
		ClusterSize = NewClusterSize;
	}

	virtual void ReinitializeAttack(const float InitDamage, const bool bPierce, const float InitDamageArea);
	void DebugClusterMessage();
};
