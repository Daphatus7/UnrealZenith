// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Interactable.generated.h"

UCLASS()
class ZENITH_API AInteractable : public AActor
{
	GENERATED_BODY()
	//Scene
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Scene;
	
	//Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	
	//Box Collision
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxCollision;

	//timeline
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Component", meta = (AllowPrivateAccess = "true"))
	UTimelineComponent* Timeline;

	//Texture Render Target 2D
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Ground Blend", meta = (AllowPrivateAccess = "true"))
	UTextureRenderTarget2D* TextureRenderTarget;

	//bool Enable Ground Blend
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Blend", meta = (AllowPrivateAccess = "true"))
	bool bEnableGroundBlend;

	//float Outline Draw
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground Blend", meta = (AllowPrivateAccess = "true"))
	float OutlineDraw;
	
public:
	// Sets default values for this actor's properties
	AInteractable();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
