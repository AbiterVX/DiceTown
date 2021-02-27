// Fill out your copyright notice in the Description page of Project Settings.


#include "BPLibraryUtils.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

//make空的Json对象
FStructJsonObject UBPLibraryUtils::makeJson()
{
	FStructJsonObject structJsonObject;
	return structJsonObject;
}

//通过string创建Json对象，反序列化
FStructJsonObject UBPLibraryUtils::createJson(FString jsonString)
{
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(new FJsonObject());
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(jsonString);
	FJsonSerializer::Deserialize(Reader, jsonObject);

	FStructJsonObject structJsonObject;
	structJsonObject.jsonObject = *jsonObject;
	return structJsonObject;
}

//为Json对象添加int字段
FStructJsonObject UBPLibraryUtils::setNumberValue(FStructJsonObject structJsonObject, FString keyName, int value)
{
	structJsonObject.jsonObject.SetNumberField(keyName, value);
	return structJsonObject;
}

FStructJsonObject UBPLibraryUtils::setStringValue(FStructJsonObject structJsonObject, FString keyName, FString value)
{
	structJsonObject.jsonObject.SetStringField(keyName, value);
	return structJsonObject;
}

FStructJsonObject UBPLibraryUtils::setNumberArrayValue(FStructJsonObject structJsonObject, FString keyName, TArray<int> value)
{
	TArray<TSharedPtr<FJsonValue>> valueArray;
	for (int i = 0; i < value.Num();i++) {
		TSharedPtr<FJsonValue> jsonValue = MakeShareable(new FJsonValueNumber(value[i]));
		valueArray.Add(jsonValue);
	}

	structJsonObject.jsonObject.SetArrayField(keyName, valueArray);
	return structJsonObject;
}

//从Json对象获取int字段
int UBPLibraryUtils::getNumberValue(FStructJsonObject structJsonObject, FString keyName)
{
	return structJsonObject.jsonObject.GetNumberField(keyName);
}

FString UBPLibraryUtils::getStringValue(FStructJsonObject structJsonObject, FString keyName)
{
	return structJsonObject.jsonObject.GetStringField(keyName);
}

TArray<int> UBPLibraryUtils::getNumberArrayValue(FStructJsonObject structJsonObject, FString keyName)
{
	TArray<int> result;
	TArray<TSharedPtr<FJsonValue>> valueArray = structJsonObject.jsonObject.GetArrayField(keyName);
	for (int i = 0; i < valueArray.Num(); i++) {
		result.Add(valueArray[i]->AsNumber());
	}
	return result;
}

//序列化Json对象
FString UBPLibraryUtils::serializeJson(FStructJsonObject structJsonObject)
{
	FString jsonString;
	TSharedRef<TJsonWriter<>> jsonWriter = TJsonWriterFactory<>::Create(&jsonString);
	TSharedPtr<FJsonObject> jsonObject = MakeShareable(&structJsonObject.jsonObject);
	FJsonSerializer::Serialize(jsonObject.ToSharedRef(), jsonWriter);
	return jsonString;
}

