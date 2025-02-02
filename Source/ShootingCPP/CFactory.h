#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CEnemy.h"
#include "CFactory.generated.h"

UCLASS()
class SHOOTINGCPP_API ACFactory : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFactory();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* EnemyPosition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DelayTime = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ACEnemy> EnemyFactory;

	UFUNCTION()
	void MakeEnemy();
};