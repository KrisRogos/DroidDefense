// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidDefense.h"
#include <string>
#include "C_MapMngr.h"


// Sets default values
AC_MapMngr::AC_MapMngr()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // get the blueprints
    static ConstructorHelpers::FObjectFinder<UBlueprint> bp_Tile (TEXT ("Blueprint'/Game/DroidDefense/BP_Tile.BP_Tile'"));
    if (bp_Tile.Object) mBP_Tile = (UClass*)bp_Tile.Object->GeneratedClass;
    
#if WITH_EDITOR
    SpawnFloor ();
#endif
}

// Called when the game starts or when spawned
void AC_MapMngr::BeginPlay()
{
	Super::BeginPlay();
	
#if WITH_EDITOR

#else
    SpawnFloor ();
#endif
    

}

void AC_MapMngr::SpawnFloor ()
{
    UWorld* world = GetWorld ();

    if (world)
    {
        // create the map
        for (uint8 row = 0; row < mpr_Tiles.size (); row++)
        {
            for (uint8 column = 0; column < mpr_Tiles[row].size (); column++)
            {
                // create the tile
                FVector loc = FVector (row * 400, column * 400, 0);
                FRotator rot = FRotator::ZeroRotator;
                std::string nameSt = "[ " + std::to_string (row) + " | " + std::to_string (column) + " ]";
                FName nameU (nameSt.c_str ());
                FActorSpawnParameters asp;
                asp.Name = nameU; //("[ " + std::to_string (row) + " | " + std::to_string (column) + " ]");
                asp.Owner = this;
                mpr_Tiles[row][column] = world->SpawnActor<AC_WorldTile> (mBP_Tile, loc, rot, asp);
#if WITH_EDITOR
                mpr_Tiles[row][column]->SetFolderPath ("WorldTiles");
#endif


                // set up the location
                mpr_Tiles[row][column]->X = column;
                mpr_Tiles[row][column]->Y = row;
            }
        }
    }
}

// Called every frame
void AC_MapMngr::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

