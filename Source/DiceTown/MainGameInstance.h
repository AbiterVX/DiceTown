// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MainGameMode.h"
#include "MainGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class DICETOWN_API UMainGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PlayerInfo")
	FStructPlayer playerInfo;



public:
	static const FString uiPath;

	UFUNCTION(BlueprintCallable, Category = "Resource")
	UTexture2D* loadTexture(FString textureName);
};
