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

	do
	{
		printf("\n1) Ingrese su fecha: ");
		scanf("%d%d%d", &ptralumno->fecha_nacimiento.dia, &ptralumno->fecha_nacimiento.mes, &ptralumno->fecha_nacimiento.anio);
		if(!verificarFecha(ptralumno->fecha_nacimiento.dia, ptralumno->fecha_nacimiento.mes, ptralumno->fecha_nacimiento.anio))
		{
			imprimir_error("Error. Fecha invalida");
		}
	}while(!verificarFecha(ptralumno->fecha_nacimiento.dia, ptralumno->fecha_nacimiento.mes, ptralumno->fecha_nacimiento.anio);

	do
	{
		printf("\n1) Ingrese el correo: ");
		fgets(ptralumno->correo, sizeof(ptralumno->correo), stdin);
		size_t len = strlen(ptralumno->correo);
		if (len > 0 && ptralumno->correo[len - 1] == '\n') 
		{
        		ptralumno->correo[len - 1] = '\0';
    		}
		if(!verificarCorreo(ptralumno->correo))
			imprimir_error("Error. Correo invalido");
	}while(!verificarCorreo(ptralumno->correo);
		
	do
	{
		printf("\n1) Ingrese su telefono: ");
		fgets(ptralumno->telefono, sizeof(ptralumno->telefono), stdin);
		size_t len = strlen(ptralumno->telefono);
		if (len > 0 && ptralumno->telefono[len - 1] == '\n') 
		{
        		ptralumno->telefono[len - 1] = '\0';
    		}
		if(!verificarTelefono(ptralumno->telefono))
			imprimir_error("Error. Telefono invalido");
	}while(!verificarTelefono(ptralumno->telefono);


}
