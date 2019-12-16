// Fill out your copyright notice in the Description page of Project Settings.

#include "Movimiento.h"
#include "Jugador.h"


// Sets default values
AJugador::AJugador()
{
 	// Activa o desactiva el evento Tick(evento que se llama 30 veces por fotograma),por defecto esta en True pero se recomienda desactivarlo 
	// a no ser de un caso muy excepcional.
	PrimaryActorTick.bCanEverTick = false;

	///Se crea los componentes del jugador, o mejor dicho se inicializan
		//Camara
		camaraJugador = CreateDefaultSubobject<UCameraComponent>(TEXT("Camara del jugador"));

		//SpringArm
		springArmCamara = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm de la camara"));

		//Colision con forma de capsula
		//colisionCapsula = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Colision del jugador"));

		//SkeletalMesh
		aspectoJugador = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Aspecto del jugador"));

		camaraJugador->bUsePawnControlRotation = true;

	///Une los componentes al objeto o mejor dicho creamos la jerarquia de componentes que tendra el jugador
		//Definimos como componente raiz/padre la capsula de colision
		//RootComponent = colisionCapsula; //Si no se pone esta linea no pasa nada, la raiz/padre del resto de objetos sera un objeto vacio

		//Unimos a este componente raiz tanto el "avatar" del jugador y el springArm
			aspectoJugador->SetupAttachment(RootComponent);
			springArmCamara->SetupAttachment(RootComponent);

			//Unimos la camara al springArm para que se aplique ese efecto de fluidez explicado previamente
			camaraJugador->SetupAttachment(springArmCamara);
}

// Called when the game starts or when spawned
void AJugador::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AJugador::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

//Esta funcion se llamara cada vez que solo se pulse una tecla definida en la lista de ProyectSettings->Input
void AJugador::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	//Al pulsar W o S se llamara a la funcion moverAdelanteAtras
	PlayerInputComponent->BindAxis("MueveAdelanteAtras", this, &AJugador::moverAdelanteAtras);

	//Al pulsar A o D se llamara a la funcion moverAdelanteAtras
	PlayerInputComponent->BindAxis("MueveIzquierdaDerecha", this, &AJugador::moverIzquierdaDerecha);

	//Al mover el mouse arriba o hacia abajo mueve la camara
	PlayerInputComponent->BindAxis("MiraArribaAbajo", this, &AJugador::moverCamaraArribaAbajo);

	//Al mover el mouse izquierda o derecha mueve la camara
	PlayerInputComponent->BindAxis("MiraIzquierdaDerecha", this, &AJugador::moverCamaraIzquierdaDerecha);

}

//Mover al jugador de adelante y hacia atras
void AJugador::moverAdelanteAtras(float velocidad) {
	//Si el componente que contiene todos los parametros de velocidad y movimiento existe y el jugador no esta parado...
	if (Controller != NULL && velocidad != 0.0f) {
		//...entonces se desplaza hacia adelante o hacia atras dependiendo del parametro scale visto en ProyectSettings->Input
		AddMovementInput(GetActorForwardVector(), velocidad);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Adelante")));
	}
}

//Funcion para mover al jugador hacia la izquierda o hacia la derecha
void AJugador::moverIzquierdaDerecha(float velocidad) {
	//Si el componente que contiene todos los parametros de velocidad y movimiento existe y el jugador no esta parado...
	if (Controller != NULL && velocidad != 0.0f) {
		//...entonces se desplaza hacia la izquierda o derecha dependiendo del parametro scale visto en ProyectSettings->Input
		AddMovementInput(GetActorRightVector(), velocidad);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Atras")));
	}
}

//Funcion para mover la camara del jugador arriba o abajo
void AJugador::moverCamaraArribaAbajo(float rotacion) {
	//Si el componente no es nulo mueve la camara, este componente tambien tiene parametros relacionados con la camara 
	if (Controller != NULL) {
		//Mueve la camara aplicando el scale para diferenciar de arriba hacia abajo
		AddControllerPitchInput(rotacion);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Arriba")));
	}
}

//Funcion para mover la camara del jugador de derecha a izquierda
void AJugador::moverCamaraIzquierdaDerecha(float rotacion) {
	//Si el componente no es nulo mueve la camara, este componente tambien tiene parametros relacionados con la camara 
	if (Controller != NULL) {
		//Mueve la camara aplicando el scale para diferenciar de derecha hacia izquierda
		AddControllerYawInput(rotacion);
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("abajo")));
	}
}
