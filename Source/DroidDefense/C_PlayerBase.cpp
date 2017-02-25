// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidDefense.h"
#include "C_PlayerBase.h"


// Sets default values
AC_PlayerBase::AC_PlayerBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_PlayerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

