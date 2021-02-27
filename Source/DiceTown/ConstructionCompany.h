// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MainGameMode.h"
#include "ConstructionCompany.generated.h"

/**
 * 
 */




UCLASS()
class DICETOWN_API UConstructionCompany : public UObject
{
	GENERATED_BODY()
public:
	void init(EGameType _gameType, bool _inOrder = true);

	//网络同步
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	virtual bool IsSupportedForNetworking() const override {
		return true;
	}

public:
	//向商店列表随机添加建筑
	UFUNCTION(BlueprintCallable)
	bool addBuildingRandom();

	//向商店列表添加建筑
	UFUNCTION(BlueprintCallable)
	bool addBuilding(int _buildingId);

	//建筑商店卖出建筑
	UFUNCTION(BlueprintCallable)
	bool sellBuilding(FName _buildingRowName);

private:
	void resortBuildingList();
public:
	//建筑列表(Replicated)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "ConstructionCompany")
	TArray<FStructBuildingGroup> buildingList;

	//库存(Replicated)
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Replicated, Category = "ConstructionCompany")
	TArray<int> buildingInventory;

private:
	//游戏玩法类型-增加扩展包(Replicated)
	UPROPERTY(Replicated)
	EGameType gameType;
	//按顺序(Replicated)
	UPROPERTY(Replicated)
	bool inOrder;
};
