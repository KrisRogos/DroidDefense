// Copyright Kris Rogos

#pragma once

#include "GameFramework/Actor.h"
#include "C_PathNode.generated.h"

UCLASS()
class DROIDDEFENSE_API AC_PathNode : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AC_PathNode();

    UPROPERTY (EditAnywhere, DisplayName = "X id", Category = "Path finding")
        uint8 X;

    UPROPERTY (EditAnywhere, DisplayName = "Y id", Category = "Path finding")
        uint8 Y;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
