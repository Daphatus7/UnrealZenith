// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS(Blueprintable)
class ZENITH_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

	//Volume
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* SpawnVolume;

public:
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual FVector GetARandomSpawnPoint() const;

	//register to game mode
	UFUNCTION(BlueprintCallable, Category = "Spawning")
	void RegisterToGameMode();
};
