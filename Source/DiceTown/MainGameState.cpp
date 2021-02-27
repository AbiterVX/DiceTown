// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameState.h"
#include "ConstructionCompany.h"
#include "Net/UnrealNetwork.h" 
#include "Building.h"
#include "Engine/ActorChannel.h"
#include "Net/DataBunch.h"
#include "Engine/EngineTypes.h"
#include "MainGameMode.h"
#include "Engine/World.h"




//----------- AMainGameState
int AMainGameState::MaxPlayerNum = 5;
int AMainGameState::maxState = 3;
int AMainGameState::diceCountMax = 2;

int AMainGameState::getDiceCountMax()
{
	return diceCountMax;
}

int AMainGameState::getMaxPlayerNum()
{
	return MaxPlayerNum;
}

int AMainGameState::getMaxState()
{
	return maxState;
}


void AMainGameState::startNextRound()
{
	if (HasAuthority()) {
		AMainGameMode* gameMode = (AMainGameMode*)(GetWorld()->GetAuthGameMode());
		currentRound += 1;
		currentPlayerIndex += 1;
		if (currentPlayerIndex >= gameMode->playerList.Num()) {
			currentPlayerIndex %= gameMode->playerList.Num();
		}
	}	
}

void AMainGameState::startNextState()
{
	if (currentCityState == maxState) {
		currentCityState = 1;
	}
	else {
		currentCityState += 1;
	}
}

bool AMainGameState::isDiceState()
{
	if (currentCityState == 1) {
		return true;
	}
	return false;
}

bool AMainGameState::isTriggerState()
{
	if (currentCityState == 2) {
		return true;
	}
	return false;
}

bool AMainGameState::isBuildState()
{
	if (currentCityState == 3) {
		return true;
	}
	return false;
}

AMainGameState::AMainGameState()
{
	bReplicates = true;
}

void AMainGameState::init(EGameType _gameType)
{
	//回合&阶段
	currentRound = 1;
	currentCityState = 1;
	currentStateEnd = false;
	//玩家
	currentPlayerIndex = 0;
	//建筑商店
	buildingShop = NewObject<UConstructionCompany>();
	buildingShop->init(_gameType);
	//骰子
	diceCount = 1;

}

bool AMainGameState::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{
	bool bWroteSomething = Super::ReplicateSubobjects(Channel, Bunch, RepFlags);
	bWroteSomething |= Channel->ReplicateSubobject(buildingShop, *Bunch, *RepFlags);

	return bWroteSomething;
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, buildingShop);
	DOREPLIFETIME(AMainGameState, currentPlayerIndex);
	DOREPLIFETIME(AMainGameState, currentRound);
	DOREPLIFETIME(AMainGameState, currentCityState);
	DOREPLIFETIME(AMainGameState, currentStateEnd);
	
	//DOREPLIFETIME(AMainGameState, currentDicePoint);
}

/*
void AMainGameState::setDicePoint(TArray<int> _currentDicePoint)
{
	currentDicePoint = _currentDicePoint;
}*/


