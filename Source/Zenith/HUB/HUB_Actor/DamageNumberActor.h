// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageNumberActor.generated.h"

UCLASS()
class ZENITH_API ADamageNumberActor : public AActor
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWidgetComponent * DamageNumber;
	//Cube mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Cube;
public:
	// Sets default values for this actor's properties
	ADamageNumberActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Blueprint callable event
	UFUNCTION(BlueprintImplementableEvent, Category="Actions")
	void DisplayDamage(float Damage);
};
