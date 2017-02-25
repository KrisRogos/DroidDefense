// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "C_WorldTile.generated.h"

UCLASS()
class DROIDDEFENSE_API AC_WorldTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_WorldTile();

    UPROPERTY (EditAnywhere, DisplayName = "X id", Category = "World Tile")
        uint8 X;

    UPROPERTY (EditAnywhere, DisplayName = "XY id", Category = "World Tile")
        uint8 Y;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
