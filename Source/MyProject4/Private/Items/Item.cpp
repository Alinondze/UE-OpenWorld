


#include "Items/Item.h"
#include "Components/SphereComponent.h"

AItem::AItem()
{

	PrimaryActorTick.bCanEverTick = true;

	

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent = ItemMesh;

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(GetRootComponent());

	


}


void AItem::BeginPlay()
{
	Super::BeginPlay();
	
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnSphereOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AItem::OnSphereEndOverlap);
}

void AItem::OnSphereOverlap(UPrimitiveComponent* OverlappedComponet, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		const FString OtherActorName = OtherActor->GetName();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, OtherActorName);
		}
	}

}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

	if (OtherActor)
	{
		const FString OtherActorName = OtherActor->GetName();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(1, 30.f, FColor::Red, OtherActorName);
		}
	}

}

void AItem::HandleIdleMovement(float DeltaTime)
{
	RunningTime += DeltaTime;

	float DeltaZ = Amplitude * FMath::Sin(RunningTime * TimeConstant);

	AddActorWorldOffset(FVector(0.f, 0.f, DeltaZ));
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsPickedUp) return;

	HandleIdleMovement(DeltaTime);
	

}

