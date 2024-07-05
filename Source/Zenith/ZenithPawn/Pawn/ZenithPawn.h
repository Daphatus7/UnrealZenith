// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "Zenith/Utilitise/Notification/Notification.h"
#include "ZenithPawn.generated.h"

class UAttackComponent;

UCLASS(Abstract)
class ZENITH_API AZenithPawn : public ACharacter, public INotification
{
	GENERATED_BODY()


	
	//damage Widget
	static UClass* DamageBlueprintClass;

public:
	// Sets default values for this actor's properties
	AZenithPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	
	virtual void Tick(float DeltaTime) override;
	virtual void OnTakingDamage(const float DamageAmount, AActor* DamageCauser);
	UFUNCTION(BlueprintNativeEvent, Category = "Die")
	void OnDeath();
	virtual void OnTakeDamageEffect(float DamageAmount);
	virtual void Notify() override;
};