#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CBullet.h"
#include "CPlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API ACPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ACPlayerPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* FirePosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Speed = 500.0f;
	float h;
	float v;
	int32 randRate = 30;

	void Onhorizontal(float value);
	void OnVertical(float value);



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACBullet> BulletFactory;

	void OnFire();
};