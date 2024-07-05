// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"

#include "Kismet/GameplayStatics.h"
#include "Zenith/GameMode/ZenithGameMode.h"


// Sets default values
ASpawnVolume::ASpawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	RootComponent = SpawnVolume;
	//remove collision
	SpawnVolume->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//set size
	SpawnVolume->SetBoxExtent(FVector(100, 100, 100));
}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	RegisterToGameMode();
}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector ASpawnVolume::GetARandomSpawnPoint() const
{
	const FVector SpawnOrigin = SpawnVolume->Bounds.Origin;
	const FVector SpawnExtent = SpawnVolume->Bounds.BoxExtent;
    return FMath::RandPointInBox(FBox(SpawnOrigin - SpawnExtent, SpawnOrigin + SpawnExtent));
}

void ASpawnVolume::RegisterToGameMode()
{
	if(AGameModeBase* GameMode = UGameplayStatics::GetGameMode(GetWorld()))
	{
		if(AZenithGameMode* ZenithGameMode = Cast<AZenithGameMode>(GameMode))
		{
			ZenithGameMode->AddSpawnVolume(this);
		}
	}
}

