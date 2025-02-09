// Fill out your copyright notice in the Description page of Project Settings.

#include "DroidDefense.h"
#include <string>
#include "C_MapMngr.h"



// Sets default values
AC_MapMngr::AC_MapMngr()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_MapMngr::BeginPlay()
{
    Super::BeginPlay();
    
    SpawnFloor ();
    

}

void AC_MapMngr::EndPlay (const EEndPlayReason::Type EndPlayReason)
{

    for (uint8 row = 0; row < mpr_Tiles.size (); row++)
    {
        for (uint8 column = 0; column < mpr_Tiles[row].size (); column++)
        {
            mpr_Tiles[row][column]->Destroy ();
        }
    }

    Super::EndPlay (EndPlayReason);
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

                mpr_Tiles[row][column] = SpawnSingleTile(loc);
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

bool AC_MapMngr::CheckTile (int a_X, int a_Y)
{
    // validate input
    if (a_X < 0 || a_Y < 0 || a_X >= kCols || a_Y >= kRows)
        return false;

    // true if empty
    if (mpr_Tiles[a_X][a_Y]->m_Status == EMapStatus::EMPTY)
    {
        return true;
    }
    return false;
}

bool AC_MapMngr::SetTile (int a_X, int a_Y, AC_BasicTower * a_tower)
{
    // validate input
    if (a_X < 0 || a_Y < 0 || a_X >= kCols || a_Y >= kRows)
        return false;

    // if empty, set to full and save a reference to the tower
    if (mpr_Tiles[a_X][a_Y]->m_Status == EMapStatus::EMPTY)
    {
        mpr_Tiles[a_X][a_Y]->m_Status = EMapStatus::TOWER;
        mpr_Tiles[a_X][a_Y]->m_Tower = a_tower;
        return true;
    }
    return false;
}

bool AC_MapMngr::ResetTile (int a_X, int a_Y)
{
    // validate input
    if (a_X < 0 || a_Y < 0 || a_X >= kCols || a_Y >= kRows)
        return false;

    // if empty, set to full and save a reference to the tower
    mpr_Tiles[a_X][a_Y]->m_Status = EMapStatus::EMPTY;

    return false;
}

TArray<FPathNode> & AC_MapMngr::BuildPath (FStarNode * a_Target, TArray<FPathNode> & a_array)
{
    return (GetFrom(a_Target, a_array));
}

TArray<FPathNode> & AC_MapMngr::GetFrom (FStarNode * a_Taget, TArray<FPathNode> & a_array)
{
    if (a_Taget->cameFrom == NULL)
    {
        // last item, add it
        int i = a_array.AddDefaulted ();
        a_array[i].X = a_Taget->X; 
        a_array[i].Y = a_Taget->Y;
        a_array[i].value = a_Taget->value;

        // go up
        return a_array;
    }
    else
    {
        // recursive
        GetFrom (a_Taget->cameFrom, a_array);

        // add this one
        int i = a_array.AddDefaulted ();
        a_array[i].X = a_Taget->X;
        a_array[i].Y = a_Taget->Y;
        a_array[i].value = a_Taget->value;

        // go up
        return a_array;
    }
}

bool AC_MapMngr::EvaluateNeighbor (int a_X, int a_Y, int a_Score, FStarNode* a_CameFrom, FStarNode* a_Goal,std::vector<FStarNode*>& apv_Open, std::vector<FStarNode*>& apv_Closed)
{
    FStarNode* p_Neighbor = new FStarNode (a_X, a_Y, a_Score, a_CameFrom);

    // has it been evaluated before? No need to repeat the process
    if (Find (p_Neighbor, apv_Closed) != -1)
        return false;

    // evaluate cost properly
    bool validPath = false;
    p_Neighbor->score = EvaluateCost (p_Neighbor, a_Score, validPath);

    // if this is a tile with a tower, throw it onto the closed list and quit this function
    if (!validPath)
    {
        apv_Closed.emplace_back (p_Neighbor);
        return false;
    }

    // is this a completely new node? Insert it to the open list as is
    int inOpen = Find (p_Neighbor, apv_Open);
    if (inOpen == -1)
    {
        p_Neighbor->value = p_Neighbor->score + EvaluateHeuristic (p_Neighbor, a_Goal);
        apv_Open.emplace_back (p_Neighbor);
        Sort (apv_Open);
        return true;
    }

    // compare the score, leave if the older node was better
    if (apv_Open[inOpen]->score <= p_Neighbor->score)
        return false;

    // the new node is better, replace the old node with it
    apv_Open[inOpen]->score = p_Neighbor->score;
    apv_Open[inOpen]->value = apv_Open[inOpen]->score + EvaluateHeuristic(apv_Open[inOpen], a_Goal);
    apv_Open[inOpen]->cameFrom = p_Neighbor->cameFrom;
    Sort (apv_Open);

    // everything went well and a new node was added
    return true;
}

int AC_MapMngr::EvaluateHeuristic (FStarNode * a_Node, FStarNode * a_Goal)
{
    int ret = std::abs(a_Goal->X - a_Node->X);
    ret += std::abs (a_Goal->Y - a_Node->Y);
    
    return ret + 1;
}

int AC_MapMngr::EvaluateCost (FStarNode * a_Node, int a_PreviousCost, bool & success)
{
    // towers can't be passed through, they score a 1000
    if (mpr_Tiles[a_Node->X][a_Node->Y]->m_Status == EMapStatus::TOWER)
    {
        success = false;
        return a_PreviousCost + 1000;
    }

    // no tower, passing though this is cheap
    success = true;
    return a_PreviousCost + 1;
}

int AC_MapMngr::Find (FStarNode * val, std::vector<FStarNode*>& apv_List)
{
    int c = 0;

    for (auto itr : apv_List)
    {

        int iX = itr->X;
        int iY = itr->Y;

        int vX = val->X;
        int vY = val->Y;

        if (iX == vX && iY == vY)
        {
            return c;
        }

        c++;
    }

    return -1;
}

bool compare (FStarNode * ob1, FStarNode * ob2)
{
    return ob1->value < ob2->value;
}

void AC_MapMngr::Sort (std::vector<FStarNode*>& apv_List)
{
    std::sort (apv_List.begin (), apv_List.end (), compare);
}

TArray<FPathNode> AC_MapMngr::PathFind (int a_StartX, int a_StartY, int a_TargetX, int a_TargetY, UPARAM (ref) TArray<FPathNode> & a_array, bool & validPathCreated)
{
    // make sure not already past the goal
    if (a_StartX >= kCols || a_StartY >= kRows)
    {
        validPathCreated = true; // since no path is needed, no path is a valid path
        return a_array;
    }

    // create lists
    std::vector<FStarNode*> pv_closedList;
    std::vector<FStarNode*> pv_openList;

    // create goal node
    FStarNode* p_GoalNode = new FStarNode (a_TargetX, a_TargetY, 0);

    // create the start node
    FStarNode* p_StartNode = new FStarNode (a_StartX, a_StartY, 0);
    p_StartNode->value = EvaluateHeuristic (p_StartNode, p_GoalNode);
    pv_openList.emplace_back (p_StartNode);

    // execute the core functionality
    while (pv_openList.size () > 0)
    {
        // look at the next node
        FStarNode* p_Current = pv_openList.at (0);
        pv_openList.erase (pv_openList.begin ());

        // check if this is the goal
        if (p_Current->X == p_GoalNode->X && p_Current->Y == p_GoalNode->Y)
        {
            validPathCreated = true;
            return BuildPath (p_Current, a_array);
        }

        // move to the closed list
        pv_closedList.emplace_back (p_Current);

        // evaluate all neighbors
        if (p_Current->X < kCols - 1 && p_Current->Y >= 0) 
            EvaluateNeighbor (p_Current->X + 1, p_Current->Y, p_Current->score, p_Current, p_GoalNode, pv_openList, pv_closedList);
        if (p_Current->X > 0 && p_Current->Y < kRows) 
            EvaluateNeighbor (p_Current->X - 1, p_Current->Y, p_Current->score, p_Current, p_GoalNode, pv_openList, pv_closedList);
        if (p_Current->Y < kRows - 1 && p_Current->X >= 0)
            EvaluateNeighbor (p_Current->X, p_Current->Y + 1, p_Current->score, p_Current, p_GoalNode, pv_openList, pv_closedList);
        if (p_Current->Y > 0 && p_Current->X < kCols)
            EvaluateNeighbor (p_Current->X, p_Current->Y - 1, p_Current->score, p_Current, p_GoalNode, pv_openList, pv_closedList);
        
    }

    // if things go wrong path find to starting position and report an error
    validPathCreated = false;
    return BuildPath(p_StartNode, a_array);
}

// Called every frame
void AC_MapMngr::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

