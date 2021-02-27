// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Engine/DataTable.h"
#include "MainGameMode.generated.h"


//Enum:建筑物类型
UENUM(BlueprintType)
enum class EBuildingType : uint8
{
	//Green:仅自己掷到时会触发
	Self,
	//Red:仅其他玩家掷到时会触发
	Other,
	//Blue:任意玩家掷到时会触发
	All,
	//Purple:特殊建筑，只能建造一个
	Special,
	//Purple:地标建筑
	Landmark
};

//Enum:建筑物标志
UENUM(BlueprintType)
enum class EBuildingSymbol : uint8
{
	Plant,
	Animal,
	Shop,
	Restaurant,
	Factory,
	Landmark,
	Fish,
	None
};

//Enum:建筑物效果
UENUM(BlueprintType)
enum class EBuildingEffectType : uint8
{
	//正常获取金币
	earnMoney,
	//根据需求的标识建筑数量获取金币
	selfPlantCount,
	selfAnimalCount,
	selfShopCount,
	selfRestaurantCount,
	selfFactoryCount,
	//向某个人收钱
	collectOnePlayer,
	//向所有人收钱
	collectAllPlayer,
	//商业中心(交换)
	changeBuilding,
	//双骰子(火车站)
	getSecondDice,
	//增益(购物中心)
	buff,
	//点数相同可再来一轮
	SamePointGetOneRound,
	//重投(广播塔)
	ReRoll
};

//Struct:建筑物信息/数据表信息。
USTRUCT(BlueprintType)
struct FStructBuilding : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FStructBuilding() {
		Id = -1;
	}

	//ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	int Id;

	//名称
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	FString Name;

	//触发点数
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	TArray<int> TriggerPoints;

	//费用
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	int Cost;

	//建筑物类型
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	EBuildingType BuildingType;

	//建筑物标志
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	EBuildingSymbol BuildingSymbol;

	//建筑物特效
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	EBuildingEffectType BuildingEffectType;

	//描述
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	FString Description;

public:
	static FStructBuilding getEmptyBuildingInfo() {
		FStructBuilding emptyBuildingInfo;
		emptyBuildingInfo.Id = -1;
		return emptyBuildingInfo;
	}
};


//Struct:建筑物获得金钱
USTRUCT(BlueprintType)
struct FStructBuildingEarnMoney : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FStructBuildingEarnMoney() {
		moneyCount = 0;
	}
	//建筑名
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	FString buildingName;

	//
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Table")
	int moneyCount;

	
public:
	static FStructBuildingEarnMoney getEmptyBuildingEarnMoney() {
		FStructBuildingEarnMoney emptyBuildingEarnMoney;
		emptyBuildingEarnMoney.buildingName = "Empty";
		emptyBuildingEarnMoney.moneyCount = 0;
		return emptyBuildingEarnMoney;
	}
};

//Struct:玩家信息
USTRUCT(BlueprintType)
struct FStructPlayer
{
	GENERATED_USTRUCT_BODY()
public:
	//ID
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInfo")
	int userId;
	//密码
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInfo")
	FString password;
	//手机号
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInfo")
	FString phoneNumber;
	//头像图片路径
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInfo")
	FString headImgPath;
	//玩家昵称
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInfo")
	FString userName;

	//对局次数
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match")
	int matchNum;
	//获胜次数
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match")
	int winNum;

	//好友
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Friend")
	TArray<int> friendList;
public:
	void init(int _userId, FString _userName) {
		userId = _userId;
		userName = _userName;
		password = "";
		phoneNumber = "";
		headImgPath = "";
		matchNum = 0;
		winNum = 0;
	}
};

//Enum:消息类型
/*
UENUM(BlueprintType)
enum class EMessageType : uint8
{
	//城市整体（玩家）收益
	CityEarn,
	//城市整体（玩家）消耗
	CityCost,
	//建筑收益(自主激活)
	BuildingEarn,
	//建筑收益(由其他玩家激活)
	BuildingEarnFromOther,
	
	//建筑技能激活
	BuildingSkillActive,
};*/

//消息
USTRUCT(BlueprintType)
struct FStructMessage
{
	GENERATED_USTRUCT_BODY();
public:
	FStructMessage() {};
	FStructMessage(FName _buildingRowName, int _count, int _ownerPlayerIndex) {
		buildingRowName = _buildingRowName;
		count = _count;
		ownerPlayerIndex = _ownerPlayerIndex;
	};

	//建筑名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	FName buildingRowName;
	//建筑数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Optional")
	int count;
	//拥有者Index
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Optional")
	int ownerPlayerIndex;
	
};

//建筑商店中 建筑物组信息
USTRUCT(BlueprintType)
struct FStructBuildingGroup
{
	GENERATED_USTRUCT_BODY();
public:
	void init(FName _buildingRowName, int _count) {
		buildingRowName = _buildingRowName;
		count = _count;
	}
	//列表
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	FName buildingRowName;

	//数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	int count;
};

//玩家城市中 建筑物组信息
USTRUCT(BlueprintType)
struct FStructCityBuildingGroup
{
	GENERATED_USTRUCT_BODY();
public:
	//建筑ID
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	int buildingId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	TArray<class ABuilding*> buildingList;
};

//Enum:骰子技能
UENUM(BlueprintType)
enum class EDiceSkillType : uint8
{
	
	None,
	//
	ReRoll,
	//
	AddTwo,
};

//Enum:游戏类型
UENUM(BlueprintType)
enum class EGameType : uint8
{
	//基础
	Basic,
	//港口
	Basic_Harbour,
	//百万富翁
	Basic_Millionaire,
	//港口&百万富翁
	Basic_Harbour_Millionaire,
};


UCLASS()
class DICETOWN_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()

//----------玩家
public:
	//玩家列表
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameMode")
	TArray<class AMainPlayerController*> playerList;

	//添加玩家
	UFUNCTION(BlueprintCallable)
	bool addPlayer(class AMainPlayerController* _playerController);

	//获取当前玩家
	UFUNCTION(BlueprintCallable)
	class AMainPlayerController* getPlayer(int index);

	//----------骰子
public:
	//掷骰子
	UFUNCTION(BlueprintCallable, Category = "Dice")
		TArray<int> getDicePoint(int DiceCount);

	//骰子点数总和
	UFUNCTION(BlueprintCallable, Category = "Dice")
		static int getSumPoint(TArray<int> dicePoints);

	//两个骰子点数是否相同
	UFUNCTION(BlueprintCallable, Category = "Dice")
		static bool ifSamePoint_TwoDice(TArray<int> dicePoints);
};
