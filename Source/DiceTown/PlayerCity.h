// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MainGameMode.h"
#include "PlayerCity.generated.h"

UCLASS()
class DICETOWN_API APlayerCity : public AActor
{
	GENERATED_BODY()
	
public:	
	APlayerCity();

	//网络同步
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

//----------玩家
public:
	//玩家Index(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "PlayerIndex")
	int playerIndex;

	UFUNCTION(BlueprintCallable)
	void setPlayerIndex(int _playerIndex);
//----------建筑
public:
	//建筑List(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated,  Category = "City")
	TArray<class ABuilding*> buildingList;

	//建筑组List(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "City")
	TArray<FStructBuildingGroup> buildingGroupList;

public:
	//获得触发建筑的消息list
	UFUNCTION(BlueprintCallable)
	TArray<FStructMessage> getTriggerMessages(TArray<int> _dicePoints, EDiceSkillType _diceSkill, EBuildingType _BuildingType);

	//根据消息List触发建筑(Green&Blue)
	UFUNCTION(BlueprintCallable)
	TArray<int> triggerNormalEarn(TArray<FStructMessage> _messageList);

	//根据消息List触发建筑(Green&Blue)
	UFUNCTION(BlueprintCallable)
	TArray<int> triggerEarnByDicePoint(TArray<FStructMessage> _messageList,int _dicePoint);

	//根据消息List触发建筑(Red 支付)
	UFUNCTION(BlueprintCallable)
	TArray<int> triggerPay(TArray<FStructMessage> _messageList);

	//建筑是否被触发
	UFUNCTION(BlueprintCallable)
	static bool isBuildingPointTriggered(FStructBuilding& buildingInfo, int sumDicePoint);

	//从其他玩家获取收入
	UFUNCTION(BlueprintCallable)
	void getPayEarn(int _earnMoney);


	//添加建筑
	UFUNCTION(BlueprintCallable)
	void addBuilding(FString _buildingRowName,const FVector& _position, const FRotator& _rotator);
	//移除建筑
	UFUNCTION(BlueprintCallable)
	bool removeBuilding(int index, FString buildingName);
	//是否胜利
	UFUNCTION(BlueprintCallable)
	bool ifWin();

	//获取当前id建筑的个数
	UFUNCTION(BlueprintCallable)
	int getBuildingCount(int _buildingId);

	//获取当前类别建筑的个数
	UFUNCTION(BlueprintCallable)
	int getBuildingSymbolCount(EBuildingSymbol _buildingSymbol);
protected:
	//获取用于显示的BuildingList
	UFUNCTION(BlueprintCallable)
	TArray<FStructBuildingGroup> getUIBuildingList();

	//BuildingList重新排序
	void sortBuildingList();


//----------资金
public:
	//资金(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "City")
	int money;

	//获取用于显示的BuildingList
	UFUNCTION(BlueprintCallable)
	void setMoney(int _money);


//----------地标
public:
	//建筑List(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Landmark")
	TArray<class ABuilding*> landmarkList;

	//地标(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Landmark")
	int LandmarkCount;

	//最大地标(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Landmark")
	int LandmarkCountMax;
	

};
