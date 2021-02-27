// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "MainGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "Engine/Texture2D.h"
#include "Net/UnrealNetwork.h" 


TMap<FName,FStructBuilding> ABuilding::buildingInfoList;
TMap<FName, FStructBuildingEarnMoney> ABuilding::buildingEarnMoneyList;

ABuilding::ABuilding(){
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void ABuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABuilding, buildingIndex);
	DOREPLIFETIME(ABuilding, buildingState);
	DOREPLIFETIME(ABuilding, buildingRowName);
	DOREPLIFETIME(ABuilding, buildingCount);
}


void ABuilding::BeginPlay()
{
	Super::BeginPlay();
}

void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABuilding::init(FName _buildingRowName, int _index)
{
	buildingIndex = _index;
	buildingRowName = _buildingRowName;
	if (buildingInfoList.Num() == 0) {
		initbuildingInfoList();
	}
	
	if (buildingEarnMoneyList.Num() == 0) {
		initbuildingEarnMoneyList();
	}
}

void ABuilding::initbuildingInfoList()
{
	//得到数据表
	FString tablePath = "DataTable'/Game/DiceTown/Data/DataTable_Building.DataTable_Building'";
	UDataTable* building_DT = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *tablePath));

	//初始化
	if (building_DT != nullptr) {
		TArray<FName> RowNames = building_DT->GetRowNames();
		FStructBuilding* buildingInfo = nullptr;
		FString ContextString;
		for (FName rowName : RowNames) {
			buildingInfo = building_DT->FindRow<FStructBuilding>(rowName, ContextString);
			buildingInfoList.Add(rowName, *buildingInfo);
		}
	}
}

FStructBuilding ABuilding::getBuildingInfoById(int Id)
{
	if (buildingInfoList.Num() == 0) {
		initbuildingInfoList();
	}
	for (auto& element: buildingInfoList) {
		if (element.Value.Id == Id) {
			return element.Value;
		}
	}
	return FStructBuilding::getEmptyBuildingInfo();
}

FStructBuilding ABuilding::getBuildingInfoByName(FString rowName)
{
	if (buildingInfoList.Num() == 0) {
		initbuildingInfoList();
	}
	for (auto& element : buildingInfoList) {
		if (element.Key.ToString().Equals(rowName)) {
			return element.Value;
		}
	}
	return FStructBuilding::getEmptyBuildingInfo();
}

FString ABuilding::getBuildingRowName(int Id)
{
	if (buildingInfoList.Num() == 0) {
		initbuildingInfoList();
	}
	for (auto& element : buildingInfoList) {
		if (element.Value.Id == Id) {
			return element.Key.ToString();
		}
	}
	return "";
}

FStructBuilding& ABuilding::getBuildingInfo()
{
	return *buildingInfoList.Find(buildingRowName);
}


void ABuilding::initbuildingEarnMoneyList()
{
	//得到数据表
	FString tablePath = "DataTable'/Game/DiceTown/Data/DT_BuildingEarnMoney.DT_BuildingEarnMoney'";
	UDataTable* buildingEarnMoney_DT = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), NULL, *tablePath));

	//初始化
	if (buildingEarnMoney_DT != nullptr) {
		TArray<FName> RowNames = buildingEarnMoney_DT->GetRowNames();
		FStructBuildingEarnMoney* buildingEarnMoney = nullptr;
		FString ContextString;
		for (FName rowName : RowNames) {
			buildingEarnMoney = buildingEarnMoney_DT->FindRow<FStructBuildingEarnMoney>(rowName, ContextString);
			buildingEarnMoneyList.Add(rowName, *buildingEarnMoney);
		}
	}
}

FStructBuildingEarnMoney ABuilding::getBuildingEarnMoneyByRowName(FName rowName)
{
	if (buildingEarnMoneyList.Num() == 0) {
		initbuildingEarnMoneyList();
	}
	for (auto& element : buildingEarnMoneyList) {
		if (element.Key.IsEqual(rowName)) {
			return element.Value;
		}
	}
	
	return FStructBuildingEarnMoney::getEmptyBuildingEarnMoney();
}

ABuilding* ABuilding::spawnBuilding(UWorld* _world, FString _name, const FVector& _position, const FRotator& _rotator)
{
	FString buildingPath = "Blueprint'/Game/DiceTown/BP/Building/BP_" + _name + ".BP_" + _name + "'";
	UBlueprint* loadBP = Cast<UBlueprint>(StaticLoadObject(UBlueprint::StaticClass(), NULL, *buildingPath));
	
	ABuilding* building = _world->SpawnActor<ABuilding>(loadBP->GeneratedClass, _position, _rotator);
	return building;
}

UTexture2D* ABuilding::getBuildingDisPlayImg(int _buildingId)
{
	FString buildingName = getBuildingRowName(_buildingId);
	FString buildingPath = "Texture2D'/Game/DiceTown/Resource/UI/Building/T_" + buildingName + ".T_" + buildingName + "'";
	UTexture2D* buildingImg = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *buildingPath));
	return buildingImg;
}

EBuildingEffectType ABuilding::getBuildingEffectType()
{
	FStructBuilding currentBuildingInfo = getBuildingInfoByName(getBuildingInfo().Name);
	return currentBuildingInfo.BuildingEffectType;
}

bool ABuilding::isTriggered(int sumPoint, APlayerCity* ownPlayer, APlayerCity* currentPlayer)
{
	/*
	for (int i = 0; i < getBuildingInfo()->TriggerPoints.Num();i++) {
		if (getBuildingInfo()->TriggerPoints[i] == sumPoint) {
			if (getBuildingInfo()->BuildingType == EBuildingType::All) {
				return true;
			}
			else if (getBuildingInfo()->BuildingType== EBuildingType::Self && currentPlayer == ownPlayer) {
				return true;
			}
			else if (getBuildingInfo()->BuildingType == EBuildingType::Other && currentPlayer != ownPlayer){
				return true;
			}
		}
	}
	*/
	return false;
}

//触发后的消息
FStructMessage ABuilding::getTriggeredMessage(APlayerCity* currentCity)
{
	FStructMessage message;
	/*
	int earnCount = 0;

	UDataTable* dataTable = nullptr;
	static ConstructorHelpers::FObjectFinder<UDataTable> dataTable_EarnMoney(TEXT("DataTable'/Game/DiceTown/Data/DT_BuildingEarnMoney.DT_BuildingEarnMoney_C'"));
	if (dataTable_EarnMoney.Succeeded()) {
		dataTable = dataTable_EarnMoney.Object;
	}
	FStructBuildingEarnMoney* buildingEarnMoney = nullptr;
	if (dataTable) {
		FString ContextString;
		buildingEarnMoney = dataTable->FindRow<FStructBuildingEarnMoney>(FName(*getBuildingInfo().Name), ContextString, true);
	}

	earnCount = buildingEarnMoney->moneyCount;
	int moneyCount = earnCount * buildingCount;
	message.init(getBuildingInfo().BuildingEffectType, moneyCount, currentCity, buildingIndex);

	*/
	return message;
}

bool ABuilding::isNormalEarnEffectType(EBuildingEffectType _buildingEffectType)
{
	if (_buildingEffectType == EBuildingEffectType::earnMoney || _buildingEffectType == EBuildingEffectType::selfPlantCount ||
		_buildingEffectType == EBuildingEffectType::selfAnimalCount || _buildingEffectType == EBuildingEffectType::selfShopCount ||
		_buildingEffectType == EBuildingEffectType::selfRestaurantCount || _buildingEffectType == EBuildingEffectType::selfFactoryCount ||
		_buildingEffectType == EBuildingEffectType::earnMoney || _buildingEffectType == EBuildingEffectType::earnMoney || 
		_buildingEffectType == EBuildingEffectType::earnMoney || _buildingEffectType == EBuildingEffectType::earnMoney ) {
		return true;
	}
	return false;
}

EBuildingSymbol ABuilding::getRequiredSymbol(EBuildingEffectType _buildingEffectType)
{
	if (_buildingEffectType == EBuildingEffectType::selfPlantCount) {
		return EBuildingSymbol::Plant;
	}
	else if (_buildingEffectType == EBuildingEffectType::selfAnimalCount) {
		return EBuildingSymbol::Animal;
	}
	else if (_buildingEffectType == EBuildingEffectType::selfShopCount) {
		return EBuildingSymbol::Shop;
	}
	else if (_buildingEffectType == EBuildingEffectType::selfRestaurantCount) {
		return EBuildingSymbol::Restaurant;
	}
	else if (_buildingEffectType == EBuildingEffectType::selfFactoryCount) {
		return EBuildingSymbol::Factory;
	}
	return EBuildingSymbol::None;
}

