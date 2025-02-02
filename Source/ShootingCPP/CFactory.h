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

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class UArrowComponent* EnemyPosition;

	float CurTime = 0.0f;
	float DelTime = 2.0f;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TSubclassOf<class ACEnemy> Enemy;

	void MakeEnemy();

};