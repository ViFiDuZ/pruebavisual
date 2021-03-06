// prueba1.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

enum Direccion
{
	Derecha,
	Izquierda,
	Arriba,
	Abajo,
	Neutro,
};

struct Paleta
{
	int posX;
	int posY;

	const int anchura = 240;
	const int altura = 50;

	int keyUp;
	int keyDown;

	int puntuacion = NULL;

	int velocidad = NULL;
};

struct Barras
{
	int posX;
	int posY;

	const int anchura = 80;
	const int altura = 50;

	int puntuacion = NULL;

};

struct Bola
{
	int posY;
	int posX;

	float velocidadY = 0.0f;
	float velocidadX = 0.0f;

	int radio = 30;

	Direccion direccionY = Neutro;
	Direccion direccionX = Neutro;
};

int screenWidth = 1920; //Anchura posX
int screenHeight = 1080; //Alura posY

int boxPositionX = screenWidth / 2;
int boxPositionY = screenHeight / 2;

void MoverPaletas(Paleta &paleta)
{
	int velocidad = 15;

	if (IsKeyDown(KEY_A))
	{
		paleta.velocidad = velocidad;
		paleta.posX -= paleta.velocidad;

		if (paleta.posX < 0)
		{
			paleta.posX = 0;
			paleta.velocidad = 0;
		}
	}
	else if (IsKeyDown(KEY_D))
	{
		paleta.velocidad = velocidad;
		paleta.posX += paleta.velocidad;

		if (paleta.posX > (screenWidth - paleta.anchura))
		{
			paleta.posX = (screenWidth - paleta.anchura);
			paleta.velocidad = 0;
		}
	}

}
Paleta paleta;
Bola bola;
Barras barra[20];
float random;

int separacionBarra = 0;
void PintarBola()
{

	DrawCircle(bola.posX, bola.posY, bola.radio, WHITE);


}


void compruebaBarra(Bola &bola, Barras barra[20]) {

	for (int i = 0; i < 20; i++) {

		if (barra[i].posX != -1) {

			if ((bola.posY - (bola.radio + barra[i].altura)) < (barra[i].posY))//Comprobamos Y
			{

				if ((bola.posX + bola.radio > barra[i].posX) && (bola.posX - bola.radio < barra[i].posX + barra[i].anchura)) //Comprobamos X
				{
					bola.direccionY = Abajo;

					random = rand() % 10 + -2; //entre 1 y 5
					bola.velocidadY += random / 10; //0.0random

					random = rand() % 10 + 1; //entre 1 y 5
					bola.velocidadX += random / 10; //0.0random

					if ((bola.posX > barra[i].posX + (barra[i].anchura / 2)))
					{
						bola.direccionX = Derecha;

					}
					if ((bola.posX < barra[i].posX + (barra[i].anchura / 2)))
					{
						bola.direccionX = Izquierda;
					}

					barra[i].posX = -1;
					paleta.puntuacion++;


				}

			}

		}

	}

}

void ComprobarBolaBarraYPalo(Bola &bola, Barras barra[20], Paleta &paleta)
{

	compruebaBarra(bola, barra);

	if ((bola.posY + bola.radio) > (paleta.posY))//Comprobamos X
	{
		if ((bola.posX + bola.radio > paleta.posX) && (bola.posX - bola.radio < paleta.posX + paleta.anchura)) //Comprobamos Y
		{
			bola.direccionY = Arriba;

			random = rand() % 10 + -2; //entre 1 y 5
			bola.velocidadY += random / 10; //0.0random

			random = rand() % 10 + 1; //entre 1 y 5
			bola.velocidadX += random / 10; //0.0random

			if ((bola.posX > paleta.posX + (paleta.anchura / 2)))
			{
				bola.direccionX = Derecha;

			}
			if ((bola.posX < paleta.posX + (paleta.anchura / 2)))
			{
				bola.direccionX = Izquierda;

			}

		}
	}

	switch (bola.direccionX)
	{
	case Derecha:
		bola.posX += bola.velocidadX;
		break;

	case Izquierda:
		bola.posX -= bola.velocidadX;
		break;
	}

	switch (bola.direccionY)
	{
	case Abajo:
		bola.posY += bola.velocidadY;
		break;

	case Arriba:
		bola.posY -= bola.velocidadY;
		break;
	}
}

void Gameplay(Bola &bola, Paleta &paleta, int posX, int posY)
{
	float random1;

	if (bola.posY >= screenHeight)
	{
		bola.posX = boxPositionX;
		bola.posY = boxPositionY;
		bola.velocidadX = 0.0f;
		bola.velocidadY = 0.0f;
	}

	if (bola.posY - bola.radio <= 0)//Comprobamos Y
	{

		bola.direccionY = Abajo;
	}
	if (bola.posX - bola.radio <= 0)//Comprobamos X
	{
		bola.direccionX = Derecha;

	}

	if (bola.posX + bola.radio >= screenWidth)//Comprobamos X
	{
		bola.direccionX = Izquierda;
	}


	if (bola.velocidadX == 0 && bola.velocidadY == 0)
	{
		bola.posX = boxPositionX;
		bola.posY = boxPositionY;
		separacionBarra = 0;
		paleta.puntuacion = 0;
		for (int i = 0; i < 20; i++) {
			barra[i].posX = 15 + separacionBarra;
			separacionBarra += 95;
			barra[i].posY = 15;
		}
		bola.direccionX = Neutro;

		paleta.posX = screenWidth / 2 - (paleta.anchura / 2);

		bola.direccionY = Abajo;
		bola.velocidadY = 7.5f;
	}

}

int main()
{
	InitWindow(screenWidth, screenHeight, "raylib [core] example - mouse wheel");

	// Scrolling speed in pixels

	paleta.posY = screenWidth / 2;

	for (int i = 0; i < 20; i++) {
		barra[i].posX = 15 + separacionBarra;
		separacionBarra += 95;
	}

	barra[0].posX = screenHeight / 10 - barra[0].anchura / 2;

	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{

		MoverPaletas(paleta);
		ComprobarBolaBarraYPalo(bola, barra, paleta);

		BeginDrawing();

		ClearBackground(BLACK);

		PintarBola();

		for (int i = 0; i < 20; i++) {
			if (barra[i].posX != -1) {
				DrawRectangle(barra[i].posX, barra[i].posY, barra[i].anchura, barra[i].altura, GREEN);

			}

		}

		DrawRectangle(paleta.posX, paleta.posY, paleta.anchura, paleta.altura, RED);


		DrawText(FormatText("Points: %i", paleta.puntuacion), 100, 100, 40, RED);




		Gameplay(bola, paleta, boxPositionX, boxPositionY);

		if (paleta.puntuacion >= 10)
		{

			DrawText(FormatText("Has ganado!!!"), (80 * 9), (screenHeight / 2), 80, RED);

		}
		EndDrawing();

		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
	_getch();
}


