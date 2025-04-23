#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funciones.h"


void menu(int*);

main()
{
	FILE *archivoptr;
	int opcion;
	
	menu(&opcion);
	
	while(opcion != 8)
	{
		switch(opcion)
		{
			case 1:
				if((archivoptr = fopen("alumnos.dat","r+")) == NULL)
					printf("No se puede acceder al archivo");
				else
				{
					alumnos(archivoptr);
					fclose(archivoptr);
				}
				break;
		}
		
		menu(&opcion);
	}

}

void menu(int *opcion)
{
	do
	{
		
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|  FOREGROUND_INTENSITY );
    	printf("\n\t\t\tMENU PRINCIPAL");
    	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
		printf("\n\t============================================");
		printf("\n\t\t[1] Alumnos");
		printf("\n\t\t[2] Profesor");
		printf("\n\t\t[3] Materias");
		printf("\n\t\t[4] Grupo");
		printf("\n\t\t[5] Inscripcion");
		printf("\n\t\t[6] Actualizar promedio");
		printf("\n\t\t[7] Reportes");
		printf("\n\t\t[8] Salir");
		printf("\n\t   Elija una opcion: ");
		scanf("%d",opcion);
		printf("\t---------------------------------------------");
		if(*opcion < 1 || *opcion > 8)
		{
			system("cls");
			imprimir_error("\n\t   ** Opcion invalida. Intente de nuevo **\n");
		}
	}while(*opcion < 1 || *opcion > 8);	
}
