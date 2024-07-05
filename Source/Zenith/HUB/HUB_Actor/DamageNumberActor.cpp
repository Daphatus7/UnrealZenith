// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageNumberActor.h"

#include "Components/WidgetComponent.h"
#include "Zenith/HUB/HUB_Widget/DamageNumber.h"


// Sets default values
ADamageNumberActor::ADamageNumberActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the cube mesh
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	// Set the cube mesh as the root component
	RootComponent = Cube;
	//set invisible in game
	Cube->SetVisibility(false);
	//attach the damage number component
	DamageNumber = CreateDefaultSubobject<UWidgetComponent>(TEXT("DamageNumber"));
	DamageNumber->SetupAttachment(Cube);
	
	DamageNumber->SetWidgetSpace(EWidgetSpace::Screen);	//attach widget to the root component
	DamageNumber->SetDrawSize(FVector2D(500.f, 500.f));	//set the size of the widget
}

// Called when the game starts or when spawned
void ADamageNumberActor::BeginPlay()
{
	Super::BeginPlay();
}