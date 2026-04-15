#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"


class UGeometryCollectionComponent;
class UCapsuleComponent;
class ATreasure;

UCLASS()
class MYPROJECT4_API ABreakableActor : public AActor, public IHitInterface
{
    GENERATED_BODY()

public:
    ABreakableActor();

    virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

protected:
    virtual void BeginPlay() override;

protected:
    
    UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
    UCapsuleComponent* Capsule;

    UPROPERTY(EditAnywhere, Category = "Treasures")
    TArray<TSubclassOf<ATreasure>> TreasureClasses;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    UGeometryCollectionComponent* GeometryCollection;

    bool bBroken = false;
};