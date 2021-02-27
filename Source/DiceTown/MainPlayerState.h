// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MainGameMode.h"

#include "MainPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DICETOWN_API AMainPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	//网络同步
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;



	UFUNCTION(BlueprintCallable)
	void setPlayerInfo(int _playerIndex, int _userId, FString _userName, class APlayerCity* _playerCity);
public:
	//玩家信息(Replicated)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "PlayerInfo")
	FStructPlayer playerInfo;

	//玩家index(Replicated)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "PlayerInfo")
	int playerIndex;

	//玩家城市(Replicated)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "PlayerInfo")
	class APlayerCity* playerCity;
};
