// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "C_WorldTile.h"
#include "C_BasicTower.h"
#include "C_PathNode.h"
#include <array>
#include <vector>
#include "C_MapMngr.generated.h"

USTRUCT(BlueprintType)
struct FStarNode
{
    GENERATED_USTRUCT_BODY()

    int X;
    int Y;
    int value;
    int score;
    FStarNode* cameFrom;

    FStarNode ()
    {
        X = 0;
        Y = 0;
        score = INT_MAX;
        value = INT_MAX;
        cameFrom = NULL;
    }

    FStarNode (int a_X, int a_Y, int a_Score, FStarNode* a_CameFrom = NULL)
    {
        X = a_X;
        Y = a_Y;
        score = a_Score;
        value = INT_MAX;
        cameFrom = a_CameFrom;
    }

    inline bool operator==(const FStarNode& RHS)
    {
        return (RHS.X == X && RHS.Y == Y);
    }
};

USTRUCT (BlueprintType)
struct FPathNode
{
    GENERATED_USTRUCT_BODY ()

    //FPathNode* p_Parent;

    UPROPERTY (BlueprintReadWrite, DisplayName = "X", Category = "Path data")
    int X;

    UPROPERTY (BlueprintReadWrite, DisplayName = "Y", Category = "Path data")
    int Y;

    UPROPERTY (BlueprintReadWrite, DisplayName = "Value", Category = "Path data")
    int value;

    FPathNode ()
    {
        X = 0;
        Y = 0;
        //p_Parent = NULL;
    }

    FPathNode (int a_X, int a_Y, int a_Value/*, FPathNode* ap_parent*/)
    {
        X = a_X;
        Y = a_Y;
        value = a_Value;
        //p_Parent = ap_parent;
    }
};

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

    TArray<FPathNode> & BuildPath (FStarNode* a_Target, TArray<FPathNode> & a_array);
    TArray<FPathNode> & GetFrom (FStarNode* a_Taget, TArray<FPathNode> & a_array);


    bool EvaluateNeighbor (int a_X, int a_Y, int a_Score, FStarNode* a_CameFrom, FStarNode* a_Goal, std::vector<FStarNode*> & apv_Open, std::vector<FStarNode*> & apv_Closed);

    int EvaluateHeuristic (FStarNode* a_Node, FStarNode* a_Goal);

    int Find (FStarNode* val, std::vector<FStarNode*> & apv_List);

    void Sort (std::vector<FStarNode*> & apv_List);

public:
    UFUNCTION (BlueprintCallable, DisplayName = "Path find", Category = "Map manager")
        TArray<FPathNode> PathFind (int a_StartX, int a_StartY, int a_TargetX, int a_TargetY, TArray<FPathNode> a_array);

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    
    
};
