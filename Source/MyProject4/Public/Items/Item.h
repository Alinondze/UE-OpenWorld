
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;
class UStaticMeshComponent;
UCLASS()
class MYPROJECT4_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AItem();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponet,AActor* OtherActor,UPrimitiveComponent* OtherComp,int32 OtherBodyIndex,bool bFromSweep,const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;
public:	
	
	virtual void Tick(float DeltaTime) override;

private:

	float RunningTime = 0.f;
	float Amplitude=0.25f;
	float TimeConstant = 5.f;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	

};
