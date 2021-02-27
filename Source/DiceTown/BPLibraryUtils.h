// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Dom/JsonObject.h"
#include "BPLibraryUtils.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FStructJsonObject
{
	GENERATED_USTRUCT_BODY();
public:
	FJsonObject jsonObject;
};

//Enum:建筑物类型
UENUM(BlueprintType)
enum class EMainGameModeMessageType : uint8
{
	NewState,
	GetDicePoint,
	DiceSkill,
	BuildingActive,
	Build,
};


UCLASS()
class DICETOWN_API UBPLibraryUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//make空的Json对象
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject makeJson();
	
	//通过string创建Json对象，反序列化
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject createJson(FString jsonString);

	//为Json对象添加int字段
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject setNumberValue(FStructJsonObject structJsonObject,FString keyName,int value );

	//为Json对象添加string字段
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject setStringValue(FStructJsonObject structJsonObject, FString keyName, FString value);

	//为Json对象添加Tarray<int>字段
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject setNumberArrayValue(FStructJsonObject structJsonObject, FString keyName, TArray<int> value);


	//从Json对象获取int字段
	UFUNCTION(BlueprintCallable, Category = "Json")
	static int getNumberValue(FStructJsonObject structJsonObject, FString keyName);

	//从Json对象获取String字段
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FString getStringValue(FStructJsonObject structJsonObject, FString keyName);

	//从Json对象获取String字段
	UFUNCTION(BlueprintCallable, Category = "Json")
	static TArray<int> getNumberArrayValue(FStructJsonObject structJsonObject, FString keyName);

	//序列化Json对象
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FString serializeJson(FStructJsonObject jsonObject);


	/*
	//初始化信息: EMainGameModeMessageType::NewState 
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject getJsonObjectNewState(FStructJsonObject structJsonObject, int state, int stateIndex);

	//初始化信息: EMainGameModeMessageType::NewState 
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject getJsonObjectGetDicePoint(FStructJsonObject structJsonObject, FString keyName, int value);

	//初始化信息: EMainGameModeMessageType::NewState 
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject getJsonObjectDiceSkill(FStructJsonObject structJsonObject, FString keyName, int value);


	//初始化信息: EMainGameModeMessageType::NewState 
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject getJsonObjectBuildingActive(FStructJsonObject structJsonObject, FString keyName, int value);

	//初始化信息: EMainGameModeMessageType::NewState 
	UFUNCTION(BlueprintCallable, Category = "Json")
	static FStructJsonObject getJsonObjectBuild(FStructJsonObject structJsonObject, FString keyName, int value);
	*/
};
