// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Listener.h"
#include "Notification.generated.h"

UINTERFACE(MinimalAPI)
class UNotification : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ZENITH_API INotification
{
	GENERATED_BODY()
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
protected:
	TArray<IListener *> Listeners;
public:
	//Add Listener
	void AddListener(IListener * Listener);

	//remove
	void RemoveListener(IListener * Listener);

	//notify listeners
	virtual void Notify() = 0;
};
