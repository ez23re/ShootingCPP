#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDeadZone.generated.h"

UCLASS()
class SHOOTINGCPP_API ACDeadZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDeadZone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* BoxComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* MeshComp;

	UFUNCTION()
	void OnDeadZoneOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
