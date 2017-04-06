// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "C_WorldTile.h"
#include "C_BasicTower.h"
#include <array>
#include "C_MapMngr.generated.h"

UCLASS()
class DROIDDEFENSE_API AC_MapMngr : public AActor
{
    GENERATED_BODY ()

private:
        TSubclassOf<class AC_WorldTile> mBP_Tile;
    
public:

    const static int kRows = 18;
    const static int kCols = 9;

    // Sets default values for this actor's properties
    AC_MapMngr ();

    std::array< std::array< AC_WorldTile*, kRows >, kCols> mpr_Tiles;


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void SpawnFloor ();

    UFUNCTION (BlueprintCallable, DisplayName = "Check tile", Category = "Map manager")
        bool CheckTile (int a_X, int a_Y);

    UFUNCTION (BlueprintCallable, DisplayName = "Set tile", Category = "Map manager")
        bool SetTile (int a_X, int a_Y, AC_BasicTower* a_tower);

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    
    
};
