#include "CDeadZone.h"

ACDeadZone::ACDeadZone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACDeadZone::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACDeadZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}