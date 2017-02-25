// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidDefense.h"
#include "C_EnemySpawn.h"


// Sets default values
AC_EnemySpawn::AC_EnemySpawn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_EnemySpawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_EnemySpawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

