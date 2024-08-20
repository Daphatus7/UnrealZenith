// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackGroup.h"
#include "SpinningGroup.generated.h"

UCLASS()
class ZENITH_API ASpinningGroup : public AAttackGroup
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASpinningGroup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	//-----------------------------------Compulsory Initializers--------------------------------------
	//1. Initialize the cluster

	void UpdateMotion_Implementation(float DeltaTime) override;
	
	// Already called in RegisterAttack. This further modifies the behaviour of the attack when initialized
	virtual void InitializeAttack_Implementation(AActor* Attack) override
	{
		Attack->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		Attack->SetActorLocation(GetActorLocation());
	}
};
