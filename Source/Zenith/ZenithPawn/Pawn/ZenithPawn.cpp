// Fill out your copyright notice in the Description page of Project Settings.


#include "ZenithPawn.h"

#include "Zenith/HUB/HUB_Actor/DamageNumberActor.h"
#include "Zenith/HUB/HUB_Widget/DamageNumber.h"
#include "Zenith/Utilitise/Notification/Listener.h"

class UDamageNumber;
// Static member initialization
UClass* AZenithPawn::DamageBlueprintClass = nullptr;

// Sets default values
AZenithPawn::AZenithPawn()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Load the Blueprint class only if it has not been loaded yet
	if (!DamageBlueprintClass)
	{
		static ConstructorHelpers::FClassFinder<ADamageNumberActor> ActorBPClass(TEXT("/Game/Blueprint/BP_DamageNumberText.BP_DamageNumberText_C"));
		//debug message
		if (ActorBPClass.Succeeded())
		{
			DamageBlueprintClass = ActorBPClass.Class;
		}
	}
}

// Called when the game starts or when spawned
void AZenithPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AZenithPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZenithPawn::OnTakingDamage(const float DamageAmount, AActor* DamageCauser)
{
	OnTakeDamageEffect(DamageAmount);
	Notify();
}

void AZenithPawn::OnDeath_Implementation()
{
	Destroy();
}


void AZenithPawn::OnTakeDamageEffect(float DamageAmount)
{
	//If the blueprint class is loaded
	if (DamageBlueprintClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		//get blueprint class type
		AActor* DamageNumberText = GetWorld()->SpawnActor<AActor>(DamageBlueprintClass, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
		//set damage number
		if(DamageNumberText)
		{
			Cast<ADamageNumberActor>(DamageNumberText)->DisplayDamage(DamageAmount);
		}
		
	}
}

void AZenithPawn::Notify()
{
	//notify listeners
	for (IListener* Listener : Listeners)
	{
		if(Listener)
		Listener->NotifyListener(nullptr);
	}
}
