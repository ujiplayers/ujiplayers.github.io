// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Jugador.generated.h"

UCLASS()
class MOVIMIENTO_API AJugador : public ACharacter
{
	GENERATED_BODY()
private:

	//Funcion para mover al jugador hacia adelante o hacia atras
		void moverAdelanteAtras(float velocidad);

	//Funcion para mover al jugador hacia la izquierda o hacia la derecha
		void moverIzquierdaDerecha(float velocidad);

		//Funcion para mover la camara hacia arriba o hacia abajo
		void moverCamaraArribaAbajo(float rotacion);

		//Funcion para mover la camara hacia la izquierda o derecha abajo
		void moverCamaraIzquierdaDerecha(float rotacion);

protected:
	///Se define los componentes del jugador
		//1.Camara del jugador
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes jugador")
			UCameraComponent* camaraJugador;

		//2.SpringArm para un movimiento fluido de la camara
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes jugador")
			USpringArmComponent* springArmCamara;

		//3.SkeletalMesh, sera el "avatar" del jugador
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Componentes jugador")
			USkeletalMeshComponent* aspectoJugador;

public:
	// Sets default values for this character's properties
	AJugador();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
};
