// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructionCompany.h"
#include "Building.h"
#include "Net/UnrealNetwork.h" 




void UConstructionCompany::init(EGameType _gameType, bool _inOrder)
{
	
	gameType = _gameType;
	inOrder = _inOrder;
	
	TMap<int,int> shopBuildingList;
	int normalCount = 6;
	int specialCount = 4;
	switch (gameType)
	{
	case EGameType::Basic:
		//1 基础

		//初始建筑列表
		for (int i = 1; i <= 15;i++) {
			FStructBuildingGroup newBuildingGroup;
			newBuildingGroup.init(FName(*ABuilding::getBuildingRowName(i)), normalCount);
			buildingList.Add(newBuildingGroup);
		}
		buildingList[6].count = specialCount;
		buildingList[7].count = specialCount;
		buildingList[8].count = specialCount;
		
		break;
	case EGameType::Basic_Harbour:
		//2 港口
		break;
	case EGameType::Basic_Millionaire:
		//3 百万富翁
		break;
	case EGameType::Basic_Harbour_Millionaire:
		//4 港口&百万富翁
		break;
	default:
		break;
	}

	resortBuildingList();
}

void UConstructionCompany::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);


	DOREPLIFETIME(UConstructionCompany, buildingList);
	DOREPLIFETIME(UConstructionCompany, buildingInventory);
	DOREPLIFETIME(UConstructionCompany, gameType);
	DOREPLIFETIME(UConstructionCompany, inOrder);


}



//向商店列表里添加(补充)随机的建筑
bool UConstructionCompany::addBuildingRandom()
{
	switch (gameType)
	{
	case EGameType::Basic:
		return false;
		break;
	case EGameType::Basic_Harbour:
		break;
	case EGameType::Basic_Millionaire:
		break;
	case EGameType::Basic_Harbour_Millionaire:
		break;
	default:
		break;
	}

	/*
	if (buildingInventory.Num() > 0) {
		int index = FMath::RandRange(1, buildingInventory.Num());
		addBuilding(buildingInventory[index].buildingInfo);

		buildingInventory[index].count -= 1;
		if (buildingInventory[index].count == 0) {
			buildingInventory.RemoveAt(index);
		}
		return true;
	}*/
	return false;
}

//向商店列表添加建筑
bool UConstructionCompany::addBuilding(int _buildingId)
{
	/*
	bool existed = false;
	for (int i = 0; i < buildingList.Num();i++) {
		if (buildingList[i].buildingInfo.Id == buildingInfo.Id) {
			buildingList[i].count += 1;
			existed = true;
			break;
		}
	}
	if (!existed) {
		FStructBuildingGroup buildingGroup;
		buildingGroup.init(buildingInfo, 1);
		buildingList.Add(buildingGroup);
		buildingList.Sort([](FStructBuildingGroup A, FStructBuildingGroup B) {
			return A.buildingInfo.Id < B.buildingInfo.Id;
		});
	}*/
	return false;
}

//建筑商店卖出建筑
bool UConstructionCompany::sellBuilding(FName _buildingRowName)
{
	for (int i = 0; i < buildingList.Num();i++) {
		if (_buildingRowName == buildingList[i].buildingRowName) {
			if (buildingList[i].count > 0) {
				buildingList[i].count -= 1;
				if (buildingList[i].count == 0) {
					buildingList.RemoveAt(i);
					resortBuildingList();
				}
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

void UConstructionCompany::resortBuildingList()
{
	buildingList.Sort([](FStructBuildingGroup buildingGroupA, FStructBuildingGroup buildingGroupB) {
		int buildingA_Id = ABuilding::getBuildingInfoByName(buildingGroupA.buildingRowName.ToString()).Id;
		int buildingB_Id = ABuilding::getBuildingInfoByName(buildingGroupB.buildingRowName.ToString()).Id;
		
		return buildingA_Id < buildingB_Id;
	});
}
