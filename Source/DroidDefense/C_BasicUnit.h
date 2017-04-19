// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "C_PathNode.h"
#include "C_BasicUnit.generated.h"

UCLASS()
class DROIDDEFENSE_API AC_BasicUnit : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AC_BasicUnit ();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION (BlueprintCallable, DisplayName = "Path Find with A*", Category = "Unit Behavior")
        bool AStarTrace ();


public:
    // goal location
    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, DisplayName = "Target Location", Category = "Unit data")
    FVector m_TargetLoc;

    UPROPERTY (BlueprintReadWrite, DisplayName = "Target square X", Category = "Unit data")
        int m_TargetX;

    UPROPERTY (BlueprintReadWrite, DisplayName = "Target square Y", Category = "Unit data")
        int m_TargetY;

    // health
    UPROPERTY (BlueprintReadWrite, DisplayName = "Health", Category = "Unit data")
        float m_Health;

    UPROPERTY (BlueprintReadWrite, DisplayName = "MaxHealth", Category = "Unit data")
        float m_MaxHealth;

    UPROPERTY (BlueprintReadWrite, DisplayName = "Parts left on death", Category = "Unit data")
        int m_PartsDeath;

    // path finding
    UPROPERTY (BlueprintReadWrite, DisplayName = "Path nodes", Category = "Unit data")
        TArray<AC_PathNode*> mrp_PathNodes;

    UPROPERTY (BlueprintReadWrite, DisplayName = "Current path node", Category = "Unit data")
        int m_CurrentNode;

    UFUNCTION (BlueprintImplementableEvent, DisplayName = "Find my path", Category = "Unit behavior")
        void FindPath ();

   

    void Init (FVector a_TargetLoc);

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
};
