// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSBlackHole.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AFPSBlackHole::AFPSBlackHole()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetupAttachment(MeshComp);

	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetupAttachment(MeshComp);

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFPSBlackHole::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AFPSBlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> OtherComponents;
	TArray<UPrimitiveComponent*> ToDestroyComponents;
	OuterSphereComp->GetOverlappingComponents(OtherComponents);

	for (int i = 0; i < OtherComponents.Num(); i++) {
		OtherComponents[i]->AddRadialForce(GetActorLocation(), OuterSphereComp->GetScaledSphereRadius(), -2000, ERadialImpulseFalloff::RIF_Constant, true);

		if (InnerSphereComp->IsOverlappingComponent(OtherComponents[i])) {
			OtherComponents[i]->DestroyComponent();
		}
	}
}

