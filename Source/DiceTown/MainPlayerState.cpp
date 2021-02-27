// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerState.h"
#include "Net/UnrealNetwork.h" 
#include "PlayerCity.h"

void AMainPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainPlayerState, playerInfo);
	DOREPLIFETIME(AMainPlayerState, playerIndex);
	DOREPLIFETIME(AMainPlayerState, playerCity);
}

void AMainPlayerState::setPlayerInfo(int _playerIndex, int _userId, FString _userName, APlayerCity* _playerCity)
{
	playerIndex = _playerIndex;
	playerInfo.init(_userId, _userName);
	playerCity = _playerCity;
}
