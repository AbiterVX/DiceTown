// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Dice.generated.h"

/**
 * 
 */
UCLASS()
class DICETOWN_API UDice : public UObject
{
	GENERATED_BODY()
	

public:
	TArray<int> getDicePoint(int DiceCount);

};
