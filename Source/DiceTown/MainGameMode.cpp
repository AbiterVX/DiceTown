// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameMode.h"
#include "ConstructionCompany.h"
#include "MainPlayerController.h"



bool AMainGameMode::addPlayer(AMainPlayerController* _playerController)
{
	for (int i = 0; i < playerList.Num();i++) {
		if (_playerController == playerList[i]) {
			return false;
		}
	}
	playerList.Add(_playerController);
	return true;
}


AMainPlayerController* AMainGameMode:: getPlayer(int index)
{
	return playerList[index];
}


//----------骰子
//掷骰子
TArray<int> AMainGameMode::getDicePoint(int DiceCount)
{
	TArray<int> dicePoints;
	/*for (int i = 0; i < DiceCount; i++) {
		dicePoints.Add(FMath::RandRange(1, 6));
	}*/
	dicePoints.Add(3);
	return dicePoints;
}

//骰子点数总和
int AMainGameMode::getSumPoint(TArray<int> dicePoints)
{
	int sum = 0;
	for (int i = 0; i < dicePoints.Num(); i++) {
		sum += dicePoints[i];
	}
	return sum;
}

//两个骰子点数是否相同
bool AMainGameMode::ifSamePoint_TwoDice(TArray<int> dicePoints)
{
	bool result = false;
	if (dicePoints.Num() == 2) {
		if (dicePoints[0] == dicePoints[1]) {
			result = true;
		}
		else {
			result = false;
		}
	}
	return result;
}





