#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include "validaciones.h"
#include "Estructuras.h"

void imprimir_error(const char *);
void ingresarDatos(char *);

void alumnos(FILE *);
void materias(FILE *);
void profesores(FILE *);


void imprimir_error(const char* mensaje) 
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
    
    printf("\a %s",mensaje);
    
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ingresarDatos(char *respuestaptr)
{
	do
	{
		printf("\nDesea ingresar datos (SI/NO): ");
		fflush(stdin);
		gets(respuestaptr);
		if(strcmp(respuestaptr,"SI") != 0 && strcmp(respuestaptr,"NO") != 0 && strcmp(respuestaptr,"si") != 0 && strcmp(respuestaptr,"no") != 0)
			imprimir_error("--Opcion invalida--");
	}while(strcmp(respuestaptr,"SI") != 0 && strcmp(respuestaptr,"NO") != 0 && strcmp(respuestaptr,"si") != 0 && strcmp(respuestaptr,"no") != 0);
}

void alumnos(FILE *f_archivoptr)
{
	struct datosAlumnos alumno, *ptralumno;
	int resultado_scanf, matricula_aux;
	char respuesta[3];

	ptralumno = &alumno;
	
	ingresarDatos(respuesta);
	
	while(strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0)
	{
		
		do
		{
			printf("\n1) Ingrese la matricula: ");
			scanf("%d", &matricula_aux);
			if(matricula_aux <= 0 || matricula_aux > 100) 
				imprimir_error("--Matricula invalida (0 - 100)--");
		}while(matricula_aux <= 0 || matricula_aux > 100);
		
		fseek(f_archivoptr, (matricula_aux - 1) * sizeof(struct datosAlumnos),SEEK_SET);
		fread(&alumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
		if(alumno.matricula != 0)
			imprimir_error("--Este alumno ya esta registrado--");
		else
		{
			ptralumno->matricula = matricula_aux;
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
			printf("**************-*-*-*-**-*-%d%20s%10s",ptralumno->matricula,ptralumno->nombre,ptralumno->carrera);
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
		
			printf("\n8) Direccion: ");
			do
			{
				printf("\n\tIngrese la calle: ");
				fflush(stdin);
				gets(ptralumno->dir.calle);
				if(!(verificarDescripcion(ptralumno->dir.calle)))
					imprimir_error("\t--Solo puede incluir letras--");
			}while(!(verificarDescripcion(ptralumno->dir.calle)));
			do
			{
				printf("\n\tIngrese el numero: #");
				fflush(stdin);
				resultado_scanf = scanf("%d",&ptralumno->dir.numero);
				if(resultado_scanf != 1)
					imprimir_error("\t--Solo debe contener numeros--\n");
			}while(resultado_scanf != 1);
			do 
			{
				printf("\n\tIngrese la colonia: ");
				fflush(stdin);
				gets(ptralumno->dir.colonia);
				if(!(verificarDescripcion(ptralumno->dir.colonia)))
					imprimir_error("\t--Solo puede incluir letras y numeros--");
			} while(!(verificarDescripcion(ptralumno->dir.colonia)));
			do
			{
				printf("\n\tIngrese el municipio: ");
				fflush(stdin);
				gets(ptralumno->dir.municipio);
				if(!(verificarDescripcion(ptralumno->dir.municipio)))
					imprimir_error("\t--Solo puede incluir letras y numeros--");
			}while(!(verificarDescripcion(ptralumno->dir.municipio)));
			do
			{
				printf("\n\tIngrese el estado: ");
				fflush(stdin);
				gets(ptralumno->dir.estado);
				if(!(verificarNombre(ptralumno->dir.estado)))
					imprimir_error("\t--Solo puede incluir letras--");
			}while(!(verificarNombre(ptralumno->dir.estado)));
			
			fseek(f_archivoptr, (alumno.matricula - 1) * sizeof(struct datosAlumnos), SEEK_SET);
			fwrite(&alumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
		}
			
		ingresarDatos(respuesta);
	}
	
	//prueba
	
	rewind(f_archivoptr);
	//fseek(f_archivoptr, (100 - 1) * sizeof(struct datosAlumnos), SEEK_SET);
	fread(&alumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
	while(!feof(f_archivoptr))
	{
		if(alumno.matricula != 0)
			printf("\n\n%10d%30s%10s%\n",ptralumno->matricula,ptralumno->nombre,ptralumno->carrera);
		fread(&alumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
	}
}

void materias(FILE *f_archivoptr)
{
	struct datosMaterias materia, *materiaptr;
	int clave_aux, i;
	char respuesta[3];
	
	materiaptr = &materia;
	
	ingresarDatos(respuesta);
	
	while( strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0)
	{	
		i = 1;
		
		do
		{
			printf("\n1) Ingrese la clave de la materia: ");
			scanf("%d",&clave_aux);
			if(clave_aux <= 0 || clave_aux > 50)
				imprimir_error("--Clave invalida (0-50)");
		}while(clave_aux <= 0 || clave_aux > 50);
		fseek(f_archivoptr, (clave_aux - 1 )* sizeof(struct datosMaterias), SEEK_SET);
		fread(&*(materiaptr), sizeof(struct datosMaterias), 1, f_archivoptr);
		if(materia.clave_materia != 0)
			imprimir_error("--Esta clave ya tiene registros--");
		else
		{
			materiaptr->clave_materia = clave_aux;
			
			do
			{
				printf("\n2) Nombre de la materia: ");
				fflush(stdin);
				gets(materiaptr->nombre);
				if(!(verificarNombre(materiaptr->nombre)))
					imprimir_error("--Solo puede introducir letras--");
			}while(!(verificarNombre(materiaptr->nombre)));
			if(*(materiaptr->nombre + 0) >= 97 && *(materiaptr->nombre + 0) <= 122)
					*(materiaptr->nombre + 0) -=32;
			
			while(*(materiaptr->nombre + i) != '\0')
			{
				if(*(materiaptr->nombre + i) >= 'A' && *(materiaptr->nombre + i) <= 'Z')
					*(materiaptr->nombre + i) +=32;
				i++;	
			}
			
			do
			{
				printf("\n3) Semestre: ");
				scanf("%d",&materiaptr->semestre);
				if(materiaptr->semestre <= 0 || materiaptr->semestre > 10)
					imprimir_error("--Debe corresponder de 1-10--");
			}while(materiaptr->semestre <= 0 || materiaptr->semestre > 10);
			
			do
			{
				printf("\n4) Descripcion: ");
				fflush(stdin);
				gets(materiaptr->descripcion);
				if(!(verificarDescripcion(materiaptr->descripcion)))
					imprimir_error("--Solo debe contener letras,numeros y espacios--");
			}while(!(verificarDescripcion(materiaptr->descripcion)));
			
			fseek(f_archivoptr, (materiaptr->clave_materia - 1) * sizeof(struct datosMaterias), SEEK_SET);
			fwrite(&materia, sizeof(struct datosMaterias), 1, f_archivoptr);	
		}
		ingresarDatos(respuesta);
	}
	
	//PRUEBAAA
	printf("\n%d",materia.semestre);
	printf("\t%s",materiaptr->nombre); 
		
	rewind(f_archivoptr);
	
	fread(&materia, sizeof(struct datosMaterias), 1, f_archivoptr);
	while(!feof(f_archivoptr))
	{
		if(materia.clave_materia != 0)
			printf("\n\n%10d%30s%10d%50s%\n",materia.clave_materia, materiaptr->nombre,materia.semestre,materiaptr->descripcion);
		fread(&materia, sizeof(struct datosMaterias), 1, f_archivoptr);
	}
		
}

void profesores(FILE *f_archivoptr)
{
	struct datosProfes profesor, *profesorptr;
	struct datosMaterias materia;
	FILE *materiasptr;
	int id_aux, i = 0, resultado_scanf;
	char opcion[3];
	
	profesorptr = &profesor;
	
	ingresarDatos(opcion);
	
	while(strcmp(opcion,"SI") == 0 || strcmp(opcion,"si") == 0)
	{
		
		do
		{
			printf("\n1) No. Empleado: ");
			scanf("%d",&id_aux);
			if(id_aux <= 0 || id_aux >50)
				imprimir_error("--ID invalido (0-50)");
		}while(id_aux <= 0 || id_aux >50);
		fseek(f_archivoptr, (id_aux - 1) * sizeof(struct datosProfes), SEEK_SET);
		fread(&profesor, sizeof(struct datosProfes), 1, f_archivoptr);
		if(profesorptr->ID_empleado != 0)
			imprimir_error("--Este ID ya esta registrado--");
		else
		{
			profesorptr->ID_empleado = id_aux;
			
			do
			{
				printf("\n2) Nombre: ");
				fflush(stdin);
				gets(profesorptr->nombre);
				if(!(verificarNombre(profesorptr->nombre)))
					imprimir_error("--Solo ingresar letras y espacios--");
			}while(!(verificarNombre(profesorptr->nombre)));
			
			do
			{
				printf("\n3) Coordinacion: ");
				scanf("%d",&profesorptr->coordinacion);
				if(profesorptr->coordinacion < 1 || profesorptr->coordinacion > 6)
					imprimir_error("--Debe estar entre 1 y 6--");
			}while(profesorptr->coordinacion < 1 || profesorptr->coordinacion > 6);
			
			do
			{
				printf("\n4) Fecha de nacimiento: ");
				printf("\n\tDia: "); 
				scanf("%d",&profesorptr->fecha_nacimiento.dia);
				printf("\n\tMes: ");
				scanf("%d",&profesorptr->fecha_nacimiento.mes);
				printf("\n\tA%co: ",164); 
				scanf("%d",&profesorptr->fecha_nacimiento.anio);
				if(!(verificarFecha(profesorptr->fecha_nacimiento.dia, profesorptr->fecha_nacimiento.mes, profesorptr->fecha_nacimiento.anio)))
					imprimir_error("--Fecha invalida--");
			}while(!(verificarFecha(profesorptr->fecha_nacimiento.dia, profesorptr->fecha_nacimiento.mes, profesorptr->fecha_nacimiento.anio)));
			
			do
			{
				printf("\n5) Correo: ");
				fflush(stdin);
				gets(profesorptr->correo);
				if(!(verificarCorreo(profesorptr->correo)))
					imprimir_error("--Correo invalido--");
			}while(!(verificarCorreo(profesorptr->correo)));
			
			do
			{
				printf("\n6) Telefono: ");
				fflush(stdin);
				gets(profesorptr->telefono);
				if(!(verificarTelefono(profesorptr->telefono)))
					imprimir_error("--Telefono invalido--");
			}while(!(verificarTelefono(profesorptr->telefono)));
			
			printf("\n7) Materias que imparte: ");
			do
			{
				do
				{
					printf("\tClave de la materia: ");
					scanf("%d",&id_aux);
					if(id_aux <= 0 || id_aux > 50)
						imprimir_error("--Clave invalida (0-50)");
				}while(id_aux <= 0 || id_aux > 50);
				
				if((materiasptr = fopen("materias.dat", "r")) == NULL)
					imprimir_error("--No se puede acceder a el archivo--");
				else
				{
					fseek(materiasptr, (id_aux - 1) * sizeof(struct datosMaterias), SEEK_SET);
					fread(&materia, sizeof(struct datosMaterias), 1, materiasptr);
					if(materia.clave_materia == 0)
						imprimir_error("--No existe esta materia--");
					else 
					{
						profesorptr->ID_empleado = id_aux;
						i++;
					}	
					fclose(materiasptr);
				}
				ingresarDatos(opcion);	
				if(i > 10)
					imprimir_error("\t--Solo puede ingresar 10 materias--");
			}while(strcmp(opcion,"SI") ==0 || strcmp(opcion,"si") ==0 && i < 10 );
			
			printf("\n8) Direccion: ");
			do
			{
				printf("\n\tIngrese la calle: ");
				fflush(stdin);
				gets(profesorptr->dir.calle);
				if(!(verificarDescripcion(profesorptr->dir.calle)))
					imprimir_error("\t--Solo puede incluir letras--");
			}while(!(verificarDescripcion(profesorptr->dir.calle)));
			do
			{
				printf("\n\tIngrese el numero: #");
				fflush(stdin);
				resultado_scanf = scanf("%d",&profesorptr->dir.numero);
				if(resultado_scanf != 1)
					imprimir_error("\t--Solo debe contener numeros--\n");
			}while(resultado_scanf != 1);
			do 
			{
				printf("\n\tIngrese la colonia: ");
				fflush(stdin);
				gets(profesorptr->dir.colonia);
				if(!(verificarDescripcion(profesorptr->dir.colonia)))
					imprimir_error("\t--Solo puede incluir letras y numeros--");
			} while(!(verificarDescripcion(profesorptr->dir.colonia)));
			do
			{
				printf("\n\tIngrese el municipio: ");
				fflush(stdin);
				gets(profesorptr->dir.municipio);
				if(!(verificarDescripcion(profesorptr->dir.municipio)))
					imprimir_error("\t--Solo puede incluir letras y numeros--");
			}while(!(verificarDescripcion(profesorptr->dir.municipio)));
			do
			{
				printf("\n\tIngrese el estado: ");
				fflush(stdin);
				gets(profesorptr->dir.estado);
				if(!(verificarNombre(profesorptr->dir.estado)))
					imprimir_error("\t--Solo puede incluir letras--");
			}while(!(verificarNombre(profesorptr->dir.estado)));
			
			fseek(f_archivoptr, (profesor.ID_empleado - 1) * sizeof(struct datosProfes), SEEK_SET);
			fwrite(&profesor, sizeof(struct datosProfes), 1, f_archivoptr);
			printf("\n\tDatos guardados con exito");
		}	
		ingresarDatos(opcion);
	}
	
	//prueba
	rewind(f_archivoptr);
	fread(&profesor, sizeof(struct datosProfes), 1, f_archivoptr);
	while(!feof(f_archivoptr))
	{
		if(profesor.ID_empleado != 0)
		{
			printf("\n%5d%30s%5d%5d%30s\n",profesor.ID_empleado,profesor.nombre,profesor.fecha_nacimiento.mes,
			profesor.fecha_nacimiento.anio, profesor.correo);
		}
		fread(&profesor, sizeof(struct datosProfes), 1, f_archivoptr);
	}
}

