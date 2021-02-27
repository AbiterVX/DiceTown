// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "MainGameMode.h"
#include "Building.generated.h"




UCLASS()
class DICETOWN_API ABuilding : public AActor
{
	GENERATED_BODY()
public:
	ABuilding();
	
protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	//网络同步
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	//初始化设置
	void init(FName _buildingRowName, int _index);
	
//----------读建筑表
public:
	//建筑表信息
	static TMap<FName, FStructBuilding> buildingInfoList;

	//初始化建筑表
	static void initbuildingInfoList();

	//读表：根据Id获得建筑物数据
	UFUNCTION(BlueprintCallable)
	static FStructBuilding getBuildingInfoById(int Id);

	//读表：根据RowName获得建筑物数据
	UFUNCTION(BlueprintCallable)
	static FStructBuilding getBuildingInfoByName(FString rowName);

	//读表：得到建筑的对应RowName
	UFUNCTION(BlueprintCallable)
	static FString getBuildingRowName(int Id);

	//读表：得到建筑的信息
	UFUNCTION(BlueprintCallable)
	FStructBuilding& getBuildingInfo();


//----------读EarnMoney表
	//EarnMoney表
	static TMap<FName, FStructBuildingEarnMoney> buildingEarnMoneyList;

	//初始化建筑表
	static void initbuildingEarnMoneyList();

	//读表：根据RowName获得建筑EarnMoney数据
	UFUNCTION(BlueprintCallable)
	static FStructBuildingEarnMoney getBuildingEarnMoneyByRowName(FName rowName);
//----------建筑
public:
	//生成建筑对象
	static ABuilding* spawnBuilding(UWorld* _world, FString _name, const FVector& _position, const FRotator& _rotator);

	//获得建筑的图片
	UFUNCTION(BlueprintCallable)
	static class UTexture2D* getBuildingDisPlayImg(int _buildingId);

	//获得建筑物效果类型
	UFUNCTION()
	EBuildingEffectType getBuildingEffectType();

	//根据点数判断是否被触发
	UFUNCTION()
	bool isTriggered(int sumPoint, class APlayerCity* ownPlayer, class APlayerCity* currentPlayer);
	
	//触发后的消息
	UFUNCTION()
	FStructMessage getTriggeredMessage(APlayerCity* currentCity);

	//判断是否为NormalEarn类型
	UFUNCTION(BlueprintCallable)
	bool isNormalEarnEffectType(EBuildingEffectType _buildingEffectType);

	//获取需求的标志类型
	UFUNCTION(BlueprintCallable)
	static EBuildingSymbol getRequiredSymbol(EBuildingEffectType _buildingEffectType);
//----------属性
public:
	//在城市中的索引(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Building")
	int buildingIndex;
	//状态(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Building")
	int buildingState;
	//建筑的配表RowName(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Building")
	FName buildingRowName;
	//数量(Replicated)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Building")
	int buildingCount;
};
