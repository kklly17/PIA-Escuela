#include <stdio.h>
#include <windows.h>
#include "validaciones.h"
#include "Estructuras.h"

void alumnos (FILE *);
void imprimir_error(const char* mensaje);


void imprimir_error(const char* mensaje) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    
    printf("\a %s",mensaje);
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void alumnos(FILE *f_archivoptr)
{
	struct datosAlumnos alumno, *ptralumno;
	char *mensaje[50];

	ptralumno = &alumno;
	
	do
	{
		printf("\n1) Ingrese la matricula: ");
		scanf("%d", &ptralumno->matricula);
		if(ptralumno->matricula <= 0)
			imprimir_error("Error. Matricula invalida");
	}while(ptralumno->matricula <= 0);
	
		

	
}
