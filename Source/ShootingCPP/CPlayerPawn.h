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
	float Speed = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACBullet> BulletFactory;

	float h;
	float v;

	void OnHorizontal(float value);
	void OnVertical(float value);
	void OnFire();
};