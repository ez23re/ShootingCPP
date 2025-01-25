// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class SHOOTINGCPP_API APlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UBoxComponent* BoxComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UStaticMeshComponent* MeshComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	class UArrowComponent* FirePositionComp;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Speed = 500.0f;

	float h;
	float v;

	void OnHorizontal(float vale);
	void OnVertical(float value);

	void OnActionFire();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> BulletFactory; // ¾ê ¹¹Áö

};
