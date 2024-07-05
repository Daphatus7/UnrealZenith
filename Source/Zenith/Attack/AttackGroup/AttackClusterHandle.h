// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class IAttackClusterHandle
{
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual ~IAttackClusterHandle() {}
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual bool IsAttackActive() = 0;
};
