

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Bird1.generated.h"



UCLASS()
class MYPROJECT4_API ABird1 : public APawn
{
	GENERATED_BODY()

public:
	
	ABird1();

protected:
	
	virtual void BeginPlay() override;
private:

public:	
	
	virtual void Tick(float DeltaTime) override;

	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
