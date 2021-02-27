// Fill out your copyright notice in the Description page of Project Settings.


#include "Dice.h"


TArray<int> UDice::getDicePoint(int DiceCount)
{
	TArray<int> dicePoints;
	for (int i = 0; i < DiceCount;i++) {
		dicePoints.Add( FMath::RandRange(1, 6) );
	}
	return dicePoints;
}
