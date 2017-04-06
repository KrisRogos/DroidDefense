// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
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
    UPROPERTY(BlueprintReadWrite, DisplayName = "Target Location", Category = "Unit data")
    FVector m_TargetLoc;

    // health
    UPROPERTY (BlueprintReadWrite, DisplayName = "Health", Category = "Unit data")
        float m_Health;

    UPROPERTY (BlueprintReadWrite, DisplayName = "Parts left on death", Category = "Unit data")
        int m_PartsDeath;

    void Init (FVector a_TargetLoc);

public:	
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    
    
};
