#include <stdio.h>
#include <windows.h>
#include <string.h>
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

	ptralumno = &alumno;
	
	do
	{
		printf("\n1) Ingrese la matricula: ");
		scanf("%d", &ptralumno->matricula);
		if(ptralumno->matricula <= 0 || ptralumno->matricula > 100) 
			imprimir_error("--Matricula invalida (0 - 100)--");
	}while(ptralumno->matricula <= 0 || ptralumno->matricula > 100);
	do
	{
		printf("\n2) Nombre: ");
		fflush(stdin);
		gets(ptralumno->nombre);
		if(!(verificarNombre(ptralumno->nombre)))
			imprimir_error("--Solo debe contener letras y espacios--");
	}while(!(verificarNombre(ptralumno->nombre)));
	
	printf("\n3) Carrera: ");
	printf("\n*********************************************************\n");
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
	printf("\t\t--LISTADO DE CARRERAS--\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	printf("%-40s%-30s\n%-40s%-30s\n%-30s%-30s","LMAD - Multimedia y animacion D.","LA - Actuaria",
	"LCC - C. Computacionales","LF - Fisica", "LM - Matematicas", "LSTI - Seguridad en TI");
	printf("\n*********************************************************\n");
	do
	{
		printf("\nIngrese la carrera: ");
		fflush(stdin);
		gets(ptralumno->carrera);
		if(!(verificarCarrera(ptralumno->carrera)))
			imprimir_error("--Carrera invalida--");
	}while(!(verificarCarrera(ptralumno->carrera)));

	do
	{
		printf("\n4) Semestre: ");
		scanf("%d",&ptralumno->semestre);
		if(ptralumno->semestre <= 0 || ptralumno->semestre > 10)
			imprimir_error("--Semestre Invalido (1-10)--");
	}while(ptralumno->semestre <= 0 || ptralumno->semestre > 10);
	
	do
	{
		printf("\n5) Fecha de nacimiento: ");
		printf("\n\tDia: "); 
		scanf("%d",&ptralumno->fecha_nacimiento.dia);
		printf("\n\tMes: ");
		scanf("%d",&ptralumno->fecha_nacimiento.mes);
		printf("\n\tA%co: ",164); 
		scanf("%d",&ptralumno->fecha_nacimiento.anio);
		if(!(verificarFecha(ptralumno->fecha_nacimiento.dia, ptralumno->fecha_nacimiento.mes, ptralumno->fecha_nacimiento.anio)))
			imprimir_error("--Fecha invalida--");
	}while(!(verificarFecha(ptralumno->fecha_nacimiento.dia, ptralumno->fecha_nacimiento.mes, ptralumno->fecha_nacimiento.anio)));

	do
	{
		printf("\n6) Correo: ");
		fflush(stdin);
		gets(ptralumno->correo);
		/*size_t len = strlen(ptralumno->correo);
		if (len > 0 && ptralumno->correo[len - 1] == '\n') 
        		ptralumno->correo[len - 1] = '\0'; */
		if(!(verificarCorreo(ptralumno->correo)))
			imprimir_error("--Correo invalido--");
	}while(!(verificarCorreo(ptralumno->correo)));
		
	do
	{
		printf("\n7) Ingrese su telefono: ");
		fflush(stdin);
		gets(ptralumno->telefono);
		if(!(verificarTelefono(ptralumno->telefono)))
			imprimir_error("--Telefono invalido--");
	}while(!(verificarTelefono(ptralumno->telefono)));

}

