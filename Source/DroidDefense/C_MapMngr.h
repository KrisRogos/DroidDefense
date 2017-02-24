// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "C_WorldTile.h"
#include <array>
#include "C_MapMngr.generated.h"

UCLASS()
class DROIDDEFENSE_API AC_MapMngr : public AActor
{
    GENERATED_BODY ()

private:
        TSubclassOf<class AC_WorldTile> mBP_Tile;
	
public:	
	// Sets default values for this actor's properties
	AC_MapMngr ();

    std::array< std::array< AC_WorldTile*, 18 >, 9> mpr_Tiles;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
