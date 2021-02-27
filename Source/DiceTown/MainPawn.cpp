// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPawn.h"


AMainPawn::AMainPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AMainPawn::BeginPlay()
{
	Super::BeginPlay();
	
}


void AMainPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMainPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

