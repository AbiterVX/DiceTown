// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCity.h"
#include "Engine/World.h"
#include "Building.h"
#include "MainGameMode.h"
#include "Net/UnrealNetwork.h" 
#include "MainGameState.h"

APlayerCity::APlayerCity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	playerIndex = -1;
}

void APlayerCity::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(APlayerCity, playerIndex);
	DOREPLIFETIME(APlayerCity, buildingList);
	DOREPLIFETIME(APlayerCity, buildingGroupList);

	DOREPLIFETIME(APlayerCity, money);
	DOREPLIFETIME(APlayerCity, landmarkList);
	DOREPLIFETIME(APlayerCity, LandmarkCount);
	DOREPLIFETIME(APlayerCity, LandmarkCountMax);
	
}


void APlayerCity::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCity::setPlayerIndex(int _playerIndex)
{
	playerIndex = _playerIndex;
}

//----------建筑
//触发
TArray<FStructMessage> APlayerCity::getTriggerMessages(TArray<int> _dicePoints, EDiceSkillType _diceSkill, EBuildingType _BuildingType)
{
	//骰子点数
	int sumPoint = AMainGameMode::getSumPoint(_dicePoints);
	if (_diceSkill == EDiceSkillType::AddTwo) {
		sumPoint += 2;
	}

	//触发建筑消息List
	TArray<FStructMessage> messageList;
	for (int i = 0; i < buildingGroupList.Num(); i++) {
		FStructBuilding buildingInfo = ABuilding::getBuildingInfoByName(buildingGroupList[i].buildingRowName.ToString());
		if (isBuildingPointTriggered(buildingInfo, sumPoint) && buildingInfo.BuildingType == _BuildingType) {
			FStructMessage newMessage(buildingGroupList[i].buildingRowName, buildingGroupList[i].count, playerIndex);
			messageList.Add(newMessage);
		}
	}
	return messageList;
}

TArray<int> APlayerCity::triggerNormalEarn(TArray<FStructMessage> _messageList)
{
	TArray<int> earnMoney;
	earnMoney.Init(0, AMainGameState::getMaxPlayerNum());
	for (int i = 0; i < _messageList.Num();i++) {
		FStructBuilding buildingInfo = ABuilding::getBuildingInfoByName(_messageList[i].buildingRowName.ToString());
		EBuildingSymbol buildingSymbol = ABuilding::getRequiredSymbol(buildingInfo.BuildingEffectType);
		int requireSymbolCount = 1;
		if (buildingSymbol != EBuildingSymbol::None) {
			requireSymbolCount = getBuildingSymbolCount(buildingSymbol);
		}
		FStructBuildingEarnMoney buildingEarnMoney = ABuilding::getBuildingEarnMoneyByRowName(_messageList[i].buildingRowName);
		earnMoney[_messageList[i].ownerPlayerIndex - 1] += requireSymbolCount * _messageList[i].count * buildingEarnMoney.moneyCount;
	}
	return earnMoney;
}

TArray<int> APlayerCity::triggerEarnByDicePoint(TArray<FStructMessage> _messageList, int _dicePoint)
{
	TArray<int> earnMoney;
	earnMoney.Init(0, AMainGameState::getMaxPlayerNum());
	/*
	for (int i = 0; i < _messageList.Num(); i++) {
		FStructBuilding buildingInfo = ABuilding::getBuildingInfoByName(_messageList[i].buildingRowName.ToString());
		FStructBuildingEarnMoney buildingEarnMoney = ABuilding::getBuildingEarnMoneyByRowName(_messageList[i].buildingRowName);

		earnMoneySum[_messageList[i].ownerPlayerIndex] += buildingEarnMoney.moneyCount * buildingEarnMoney.moneyCount;
	}*/
	return earnMoney;
}

TArray<int> APlayerCity::triggerPay(TArray<FStructMessage> _messageList)
{
	TArray<int> payMoney;
	payMoney.Init(0, AMainGameState::getMaxPlayerNum());
	//
	for (int i = 0; i < _messageList.Num(); i++) {
		FStructBuildingEarnMoney buildingEarnMoney = ABuilding::getBuildingEarnMoneyByRowName(_messageList[i].buildingRowName);
		payMoney[_messageList[i].ownerPlayerIndex - 1] +=  _messageList[i].count * buildingEarnMoney.moneyCount;
	}

	//总共所需支付金额
	int payMoneySum = 0;
	for (int i = 0; i < payMoney.Num();i++) {
		payMoneySum += payMoney[i];
	}

	//如果玩家当前持有金币不足以全部支付
	if (money < payMoneySum) {
		TArray<int> newPayMoney;
		int remainMoney = money;
		//先按占比分配
		newPayMoney.Init(0, AMainGameState::getMaxPlayerNum());
		for (int i = 0; i < newPayMoney.Num();i++) {
			newPayMoney[i] = money * payMoney[i] / payMoneySum;
			remainMoney -= newPayMoney[i];
		}
		//如有剩余，按玩家index顺序逐个分配
		int currentIndex = (playerIndex - 1 + 1) % AMainGameState::getMaxPlayerNum();
		while (remainMoney > 0) {
			newPayMoney[currentIndex] += 1;
			remainMoney -= 1;
			currentIndex = (currentIndex + 1) % AMainGameState::getMaxPlayerNum();
		}
		payMoney = newPayMoney;
	}
	
	//支付
	payMoneySum = 0;
	for (int i = 0; i < payMoney.Num(); i++) {
		payMoneySum += payMoney[i];
	}
	money -= payMoneySum;

	return payMoney;
}

bool APlayerCity::isBuildingPointTriggered(FStructBuilding& buildingInfo, int sumDicePoint)
{
	for (int i = 0; i < buildingInfo.TriggerPoints.Num();i++) {
		if (sumDicePoint == buildingInfo.TriggerPoints[i]) {
			return true;
		}
	}
	return false;
}

void APlayerCity::getPayEarn(int _earnMoney)
{
	money += _earnMoney;
}

//添加建筑
void APlayerCity::addBuilding(FString _buildingRowName, const FVector &_position, const FRotator &_rotator)
{
	FStructBuilding buildingInfo = ABuilding::getBuildingInfoByName(_buildingRowName);

	if (buildingInfo.BuildingType == EBuildingType::Landmark) {
		//地标建筑

		//地标不重复	
		for (int i = 0; i < landmarkList.Num();i++) {
			if (landmarkList[i]->buildingRowName.IsEqual(FName(*_buildingRowName))) {
				return;
			}
		}
		//建筑生成&初始化
		ABuilding* tempBuilding = ABuilding::spawnBuilding(GetWorld(), _buildingRowName, _position, _rotator);
		tempBuilding->init(FName(*_buildingRowName), 1);
		//添加到List
		landmarkList.Add(tempBuilding);
	}
	else {
		//非地标建筑

		ABuilding* tempBuilding = ABuilding::spawnBuilding(GetWorld(), _buildingRowName, _position, _rotator);
		//得到新建建筑的索引值（根据当前类别建筑的个数）
		int index = 1;

		
		int buildingIndex = -1;
		FName currentRowName = FName(*_buildingRowName);
		for (int i = 0; i < buildingGroupList.Num();i++) {
			if (buildingGroupList[i].buildingRowName.IsEqual(currentRowName)) {
				buildingIndex = i;
				break;
			}
		}
		if (buildingIndex != -1) {
			buildingGroupList[buildingIndex].count += 1;
			index = buildingGroupList[buildingIndex].count;
		}
		else {
			FStructBuildingGroup newBuildingGroup;
			newBuildingGroup.init(FName(*_buildingRowName), index);
			buildingGroupList.Add(newBuildingGroup);
		}

		//初始化
		tempBuilding->init(FName(*_buildingRowName), index);
		//建筑List
		buildingList.Add(tempBuilding);
	}
	
	
}

//移除建筑
bool APlayerCity::removeBuilding(int index, FString buildingName)
{
	/*
	for (int i = 0; i < buildingList.Num();i++) {
		if (buildingList[i]->buildingInfo->Name == buildingName && buildingList[i]->buildingIndex == index) {
			buildingList.RemoveAt(i);
			return true;
		}
	}*/
	return false;
}

//是否胜利
bool APlayerCity::ifWin()
{
	if (LandmarkCount < LandmarkCountMax) {
		return false;
	}
	else if(LandmarkCount == LandmarkCountMax) {
		return true;
	}
	return false;
}


int APlayerCity::getBuildingCount(int _buildingId)
{
	
	FName buildingName = FName(*ABuilding::getBuildingRowName(_buildingId));
	for (int i = 0; i < buildingGroupList.Num();i++) {
		if (buildingName.IsEqual(buildingGroupList[i].buildingRowName)) {
			return buildingGroupList[i].count;
		}
	}
	return 0;
}

int APlayerCity::getBuildingSymbolCount(EBuildingSymbol _buildingSymbol)
{
	int sumCount = 0;
	for (int i = 0; i < buildingList.Num();i++) {
		FStructBuilding buildingInfo = ABuilding::getBuildingInfoByName(buildingList[i]->buildingRowName.ToString());
		if (buildingInfo.BuildingSymbol == _buildingSymbol) {
			sumCount += 1;
		}
	}
	return sumCount;
}

void APlayerCity::sortBuildingList()
{
	//重新排序
	buildingList.Sort([](ABuilding& buildingA, ABuilding& buildingB) {
		int buildingA_Id = buildingA.getBuildingInfo().Id;
		int buildingB_Id = buildingB.getBuildingInfo().Id;
		if (buildingA_Id < buildingB_Id) {
			return true;
		}
		else if (buildingA_Id == buildingB_Id) {
			return buildingA.buildingIndex < buildingB.buildingIndex;
		}
		else {
			return false;
		}
	});
}

void APlayerCity::setMoney(int _money)
{
	money = _money;
}

TArray<FStructBuildingGroup> APlayerCity::getUIBuildingList()
{
	//排序
	buildingGroupList.Sort([](FStructBuildingGroup A, FStructBuildingGroup B) {
		int A_id = ABuilding::getBuildingInfoByName(A.buildingRowName.ToString()).Id;
		int B_id = ABuilding::getBuildingInfoByName(B.buildingRowName.ToString()).Id;
		return A_id < B_id;
	});
	return buildingGroupList;
}




