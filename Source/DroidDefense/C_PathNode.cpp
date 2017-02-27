// Copyright Kris Rogos

#include "DroidDefense.h"
#include "C_PathNode.h"


// Sets default values
AC_PathNode::AC_PathNode()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AC_PathNode::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AC_PathNode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

