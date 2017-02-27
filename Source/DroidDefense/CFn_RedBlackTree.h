// Copyright Kris Rogos

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "C_PathNode.h"
#include "CFn_RedBlackTree.generated.h"

enum class NodeColour
{
    RED,
    BLACK
};

struct TreeNode
{
    TreeNode* p_Left;
    TreeNode* p_Right;
    TreeNode* p_Parent;
    NodeColour colour;
    AC_PathNode* data;
};

/**
 * 
 */
UCLASS()
class DROIDDEFENSE_API UCFn_RedBlackTree : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	
	
};
