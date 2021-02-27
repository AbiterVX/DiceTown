// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameInstance.h"

const FString UMainGameInstance::uiPath = FString::Printf(TEXT("/Game/DiceTown/Resource/UI/"));


UTexture2D* UMainGameInstance::loadTexture(FString textureName)
{
	FString path = uiPath + textureName + "." + textureName;
	UTexture2D* texture = LoadObject<UTexture2D>(NULL, *path);
	return texture;
}
