// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainGameMode.h"
#include "MainGameState.generated.h"






/**
 * 
 */
UCLASS()
class DICETOWN_API AMainGameState : public AGameState
{
	GENERATED_BODY()
public:
	AMainGameState();
	//初始化
	UFUNCTION(BlueprintCallable)
	void init(EGameType _gameType);
	//网络同步
	virtual bool ReplicateSubobjects(class UActorChannel* Channel, class FOutBunch* Bunch, FReplicationFlags* RepFlags) override;
	//网络同步
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

//----------玩家
public:
	//最大玩家数量 ：
	static int MaxPlayerNum;

	UFUNCTION(BlueprintCallable)
	static int getMaxPlayerNum();

	//当前回合的玩家index(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Player")
	int currentPlayerIndex;

//----------回合&阶段
public:
	//当前回合(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Round")
	int currentRound;

	//当前的阶段(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Round")
	int currentCityState;

	//最大阶段数量
	static int maxState;

	UFUNCTION(BlueprintCallable)
	static int getMaxState();

	//结束当前阶段(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Round")
	bool currentStateEnd;

	//下一回合
	UFUNCTION(BlueprintCallable)
	void startNextRound();

	//下一阶段
	UFUNCTION(BlueprintCallable)
	void startNextState();

	//当前阶段是否为骰子阶段
	UFUNCTION(BlueprintCallable)
	bool isDiceState();

	//当前阶段是否为触发阶段
	UFUNCTION(BlueprintCallable)
	bool isTriggerState();

	//当前阶段是否为购买建筑阶段
	UFUNCTION(BlueprintCallable)
	bool isBuildState();
//----------商店
public:
	//商店(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Shop")
	class UConstructionCompany* buildingShop;



//----------骰子
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dice")
	int diceCount;

	
	static int diceCountMax;

	UFUNCTION(BlueprintCallable)
	static int getDiceCountMax();
	//当前骰子点数(Replicated)
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Dice")
	//TArray<int> currentDicePoint;

	//设置骰子点数
	//UFUNCTION(BlueprintCallable)
	//void setDicePoint(TArray<int> _currentDicePoint);
};
