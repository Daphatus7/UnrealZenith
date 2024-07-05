// Fill out your copyright notice in the Description page of Project Settings.


#include "ZenithFunctionLibrary.h"

#include "Camera/CameraComponent.h"

/**
 * Simplified debug function
 * @param Message 
 * @param Tick 
 */
void UZenithFunctionLibrary::DxPrint(const FString& Message, const bool Tick)
{
 // Check if this function should display the message this tick
 if (Tick)
 {
  // Check if the GEngine pointer is valid
  if (GEngine)
  {
   // Display the message with the delta time as duration if Tick is true and GEngine is valid
   GEngine->AddOnScreenDebugMessage(-1, FApp::GetDeltaTime(), FColor::Orange, Message);
  }
 }
 else
 {
  if(GEngine)
  {
   // Display the message with a duration of 5 seconds if Tick is false and GEngine is valid
   GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, Message);
  }
 }
}

/**
 * Extend Vector in the direction by length
 * @param Vector 
 * @param Length 
 */
FVector UZenithFunctionLibrary::ExtendVector(const FVector& Vector, const float Length)
{
 return Vector.GetSafeNormal() * Length;
}

FVector UZenithFunctionLibrary::GetMouseToWorldLocation(const APlayerController* PlayerController)
{
 //mouse to world location
 FVector WorldLocation;
 FVector WorldDirection;
 PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
 
return WorldLocation;
}

FVector UZenithFunctionLibrary::GetDirectionVector(const FVector& Start, const FVector& End)
{
 return (End - Start).GetSafeNormal();
}

FVector UZenithFunctionLibrary::GetPositionInDirection(const FVector& Start, const FVector& Direction,
 const float Length)
{
 return Start + Direction.GetSafeNormal() * Length;
}


/**
 * Only works on Y-Z plane
 * @param PlayerController 
 * @param Length 
 * @return 
 */
FVector UZenithFunctionLibrary::GetFixedLengthScreenProjectionLocation(
 const APlayerController* PlayerController,const float Length)
{
 FVector WorldLocation;
 FVector WorldDirection;
 PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

 //get camera forward vector
 const FVector Forward = PlayerController->PlayerCameraManager->GetActorForwardVector();
 const float Angle = FMath::Acos(FVector::DotProduct(Forward, WorldDirection));
 //debug Angle screen
 const float Distance = Length / FMath::Cos(Angle);
 return WorldLocation + WorldDirection * Distance;
}

FVector2D UZenithFunctionLibrary::ProjectVectorToXYPlane(const FVector& Vector)
{
 return FVector2D(Vector.X, Vector.Y);
}

