/* Codigo elaborado por: Kelly Yisseth Cano Montiel 1979822 // Elva Lizeth Hernandez Gayt�n 2101295 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Estructuras.h"
#include "funciones.h"


void menu(int *);

main()
{
	FILE *archivoptr;
	int opcion;
	char submenu;
	
	menu(&opcion);
	
	while(opcion != 8)
	{
		switch(opcion)
		{
			case 1:
				if((archivoptr = fopen("alumnos.dat","r+")) == NULL)
					imprimir_error("No se puede acceder al archivo");
				else
				{
					struct datosAlumnos alumno;
					
					alumnos(archivoptr, &alumno);
					fclose(archivoptr);
				}
				break;
				
			case 2: 
				if((archivoptr = fopen("profesores.dat","r+")) == NULL)
					imprimir_error("No se puede acceder al archivo");
				else
				{
					struct datosProfes profe;
					
					profesores(archivoptr, &profe);
					fclose(archivoptr);
				}
				break;
				
			case 3: 
				if((archivoptr = fopen("materias.dat", "r+")) == NULL)
					imprimir_error("No se puede acceder al archivo");
				else
				{
					struct datosMaterias materia;
					
					materias(archivoptr, &materia);
					fclose(archivoptr);
				}
				break;	
				
			case 4:
				if((archivoptr = fopen("grupos.dat", "r+")) == NULL)
					imprimir_error("No se puede acceder al archivo");
				else
				{
					struct datosGrupos grupo;
					
					grupos(archivoptr, &grupo);
					fclose(archivoptr);
				}
				break;
			
			case 5:
				if((archivoptr = fopen("inscripcion.dat", "r+")) == NULL)
					imprimir_error("No se puede acceder al archivo");
				else
				{
					struct datosInscripcion inscripcion;
					
					inscripciones(archivoptr, &inscripcion);
					fclose(archivoptr);
				}
				break;
			
			case 6:
				if((archivoptr = fopen("alumnos.dat","r+")) == NULL)
					imprimir_error("No se puede acceder al archivo");
				else
				{
					struct datosAlumnos alumno;
					
					Actualizar_promedio(archivoptr, &alumno);
					fclose(archivoptr);
				}
				break;	
			
			case 7:
				printf("\n\n\t********************************************\n");
				printf("\t\t     SUBMENU DE REPORTES");
				printf("\n\t********************************************\n");
				printf("\n\t\ta) Listado de alumnos por carrera \n\t\tb) Lista de clases \n\t\tc) Listado de grupos por fecha \n\t\td) Minuta \n\t\te) Generar archivo de alumnos \n\t\tf) Generar archivo de profesores \n\t\tg) Mostrar archivo de texto \n\t\th) Salir");
				do
				{
					printf("\n\t   Elija una opcion: ");
					fflush(stdin);
					scanf("%c", &submenu);
					if(!(submenu >= 65 && submenu <= 72 || submenu >= 97 && submenu <= 104 ))
						imprimir_error("--\tOpcion invalida--");
				}while(!(submenu >= 65 && submenu <= 72 || submenu >= 97 && submenu <= 104 ));
				
				while(submenu != 'h' && submenu != 'H' )
				{
					switch(submenu)
					{
						case 'a': case 'A':
						
							if((archivoptr = fopen("alumnos.dat","r")) == NULL)		
								imprimir_error("No se puede acceder al archivo");
							else
							{
								struct datosAlumnos alumnor;
								Alumnos_por_carrera(archivoptr, &alumnor);
								fclose(archivoptr);
							}
							break;
						
						case 'b': case'B':
							if((archivoptr = fopen("grupos.dat", "r")) == NULL)
								imprimir_error("No se puede acceder al archivo");
							else
							{
								struct datosGrupos grupo;
								
								clases_profe(archivoptr,&grupo);
								fclose(archivoptr);
							}
							break;
						
						case'c': case'C':
							printf("\ntrabajando en ello....");
							break;
							
						case'd': case 'D':
							printf("\ntrabajando en ello....");
							break;
							
						case'e': case 'E':
							if((archivoptr = fopen("alumnos.dat","r")) == NULL)
								imprimir_error("No se puede acceder al archivo");
							else
							{
								struct datosAlumnos alumno;
								
								archivo_alumnos(archivoptr,&alumno);
								fclose(archivoptr);
							}
							break;
							
						case'f': case'F':
							if((archivoptr = fopen("profesores.dat","r")) == NULL)
								imprimir_error("No se puede acceder al archivo");
							else
							{
								struct datosProfes profe;
								
								archivo_profes(archivoptr,&profe);
								fclose(archivoptr);
							}
							break;
					}
					
					
					printf("\n\n\t********************************************\n");
					printf("\t\t     SUBMENU DE REPORTES");
					printf("\n\t********************************************\n");
					printf("\n\t\ta) Listado de alumnos por carrera \n\t\tb) Lista de clases \n\t\tc) Listado de grupos por fecha \n\t\td) Minuta \n\t\te) Generar archivo de alumnos \n\t\tf) Generar archivo de profesores \n\t\tg) Mostrar archivo de texto \n\t\th) Salir");
					do
					{
						printf("\nElija una opcion: ");
						fflush(stdin);
						scanf("%c",&submenu);
						if(!(submenu >= 65 && submenu <= 72 || submenu >= 97 && submenu <= 104 ))
							imprimir_error("--Opcion invalida--");
					}while(!(submenu >= 65 && submenu <= 72 || submenu >= 97 && submenu <= 104 ));
					
				}
				break;
			
		}

		
		
		menu(&opcion);
	}

}

void menu(int *opcionptr)
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
		scanf("%d",opcionptr);
		printf("\t---------------------------------------------\n");
		if(*opcionptr < 1 || *opcionptr > 8)
			imprimir_error("\n\t   ** Opcion invalida. Intente de nuevo **\n");
	}while(*opcionptr < 1 || *opcionptr > 8);	
}
