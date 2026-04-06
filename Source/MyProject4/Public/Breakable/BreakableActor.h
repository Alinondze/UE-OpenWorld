

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UGeometryCollectionComponent;

UCLASS()
class MYPROJECT4_API ABreakableActor : public AActor, public IHitInterface
{
	GENERATED_BODY()
	
public:	
	
	ABreakableActor();

	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;

protected:
	
	virtual void BeginPlay() override;

public:	

	
private:

	UPROPERTY(VisibleAnywhere)
	UGeometryCollectionComponent* GeometryCollection;

};
