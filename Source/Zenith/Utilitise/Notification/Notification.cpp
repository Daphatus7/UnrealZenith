// Fill out your copyright notice in the Description page of Project Settings.


#include "Notification.h"


// Add default functionality here for any INotification functions that are not pure virtual.

void INotification::AddListener(IListener * Listener)
{
	Listeners.Add(Listener);
}

void INotification::RemoveListener(IListener * Listener)
{
	Listeners.Remove(Listener);
}