#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "validaciones.h"
#include "Estructuras.h"

void imprimir_error(const char *);
void ingresarDatos(char *);

void alumnos(FILE *, struct datosAlumnos *);
void materias(FILE *, struct datosMaterias *);
void profesores(FILE *, struct datosProfes *);
void grupos(FILE *, struct datosGrupos *);
void inscripciones(FILE *, struct datosInscripcion *);
void Actualizar_promedio(FILE *, struct datosAlumnos *);
void Alumnos_por_carrera(FILE *, struct datosAlumnos *);
void clases_profe(FILE *, struct datosGrupos *);
void archivo_alumnos(FILE *, struct datosAlumnos *);
void archivo_profes(FILE *f_archivoptr, struct datosProfes *profeptr);


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

void alumnos(FILE *f_archivoptr, struct datosAlumnos *ptralumno)
{
	int resultado_scanf, matricula_aux;
	char respuesta[3];


	printf("\n\n\t\t같 REGISTRAR ALUMNOS 같\n");
	ingresarDatos(respuesta);
	
	while(strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0)
	{
		rewind(f_archivoptr);
		do
		{
			printf("\n1) Ingrese la matricula: ");
			scanf("%d", &matricula_aux);
			if(matricula_aux <= 0 || matricula_aux > 100) 
				imprimir_error("--Matricula invalida (0 - 100)--");
		}while(matricula_aux <= 0 || matricula_aux > 100);
		
		fseek(f_archivoptr, (matricula_aux - 1) * sizeof(struct datosAlumnos),SEEK_SET);
		fread(&*ptralumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
		if(ptralumno->matricula != 0)
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
			
			fseek(f_archivoptr, (ptralumno->matricula - 1) * sizeof(struct datosAlumnos), SEEK_SET);
			fwrite(&*ptralumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
		}
			
		ingresarDatos(respuesta);
	}
}

void materias(FILE *f_archivoptr, struct datosMaterias *materiaptr)
{
	int clave_aux, i;
	char respuesta[3];
	
	
	printf("\n\n\t\t같 REGISTRAR MATERIAS 같\n");
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
		fread(&*materiaptr, sizeof(struct datosMaterias), 1, f_archivoptr);
		if(materiaptr->clave_materia != 0)
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
			fwrite(&*materiaptr, sizeof(struct datosMaterias), 1, f_archivoptr);	
		}
		ingresarDatos(respuesta);
	}	
}

void profesores(FILE *f_archivoptr, struct datosProfes *profesorptr)
{
	int id_aux, i = 0, resultado_scanf;
	char opcion[3];
	
	printf("\n\n\t\t같 REGISTRAR PROFESORES 같\n");
	ingresarDatos(opcion);
	while(strcmp(opcion,"SI") == 0 || strcmp(opcion,"si") == 0)
	{
		i = 0;
		
		do
		{
			printf("\n1) No. Empleado: ");
			scanf("%d",&id_aux);
			if(id_aux <= 0 || id_aux >50)
				imprimir_error("--ID invalido (0-50)");
		}while(id_aux <= 0 || id_aux >50);
		fseek(f_archivoptr, (id_aux - 1) * sizeof(struct datosProfes), SEEK_SET);
		fread(&*profesorptr, sizeof(struct datosProfes), 1, f_archivoptr);
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
					printf("\n\tClave de la materia: ");
					scanf("%d",&id_aux);
					if(id_aux <= 0 || id_aux > 50) 
						imprimir_error("--Clave invalida (1-50)--");
					else
						if(!verificarMateria(&id_aux))
							imprimir_error("--Esta clave no esta registrada--");
				}while(id_aux <= 0 || id_aux > 50 || !verificarMateria(&id_aux));
				
				profesorptr->clave_materia[i] = id_aux;
				
				i++;
				ingresarDatos(opcion);	
				if(i > 9)
					imprimir_error("\t--Solo puede ingresar 10 materias--");
			}while(strcmp(opcion,"SI") == 0 || strcmp(opcion,"si") == 0 && i <= 9 );
			
			printf("\n8) Direccion: ");
			do
			{
				printf("\n\tIngrese la calle: ");
				fflush(stdin);
				gets(profesorptr->dir.calle);
				if(!(verificarDescripcion(profesorptr->dir.calle)))
					imprimir_error("\t--Solo puede incluir letras--");
			}while(!verificarDescripcion(profesorptr->dir.calle));
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
			} while(!verificarDescripcion(profesorptr->dir.colonia));
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
			
			fseek(f_archivoptr, (profesorptr->ID_empleado - 1) * sizeof(struct datosProfes), SEEK_SET);
			fwrite(&*profesorptr, sizeof(struct datosProfes), 1, f_archivoptr);
			printf("\n\tDatos guardados con exito");
		}	
		ingresarDatos(opcion);
	}
}

void grupos(FILE *f_archivoptr, struct datosGrupos *ptrgrupo)
{
	
	time_t fecha = time(NULL);
	struct tm *actual = localtime(&fecha);
	char respuesta[3];
	int i = 0, k = 0, id_aux, materia_aux, materias[6] = {108};
	bool materia = true;
	
	printf("\n\n\t\t같 REGISTRAR GRUPOS 같\n");
	ingresarDatos(respuesta);
	
	while(strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0)
	{
		i = 0;
		do
		{
			printf("\n1) Clave del grupo: ");
			scanf("%d",&id_aux);
			if(id_aux <= 0 || id_aux > 20)
				imprimir_error("--La clave debe ser entre 0 y 20--");
		}while(id_aux <= 0 || id_aux > 20);
		fseek(f_archivoptr, (id_aux - 1) * sizeof(struct datosGrupos), SEEK_SET);
		fread(&*ptrgrupo, sizeof(struct datosGrupos), 1, f_archivoptr);
		if(ptrgrupo->clave_grupo != 0)
			imprimir_error("--Este grupo ya esta registrado--");
		else
		{
			ptrgrupo->clave_grupo = id_aux;
			
			do
			{
				printf("\n2) Semestre: ");
				scanf("%d",&ptrgrupo->semestre);
				if(ptrgrupo->semestre <= 0 || ptrgrupo->semestre >10)
					imprimir_error("--Debe ser entre 1 y 10--");
			}while(ptrgrupo->semestre <= 0 || ptrgrupo->semestre >10);
			for( k = 0; k < 5; k++)
					materias[k] = 108;
			do
			{
				
				do
				{
					printf("\n3) Clave del profesor: ");
					scanf("%d",&id_aux);
					if(id_aux <= 0 || id_aux > 50) 
							imprimir_error("--Clave invalida (1-50)--");
					else
						if(!verificarProfesor(&id_aux))
								imprimir_error("--Este ID no esta registrado--");
				}while(id_aux <= 0 || id_aux > 50 ||!verificarProfesor(&id_aux));
				ptrgrupo->ID_empleado[i] = id_aux;
			
				do
				{
					materia = true;
					k = 0;
					printf("\n4) clave de la materia: ");
					scanf("%d",&materia_aux);
					while(k < 5 && materia)
					{
						if(materias[k] == materia_aux)
						{
							materia = false;
							imprimir_error("--Esta materia ya se ha ingresado en este grupo---");
						}
							
						k++;
					}
					
					if(materia_aux <= 0 || materia_aux > 50)
						imprimir_error("--Clave invalida (1-50)--");
					else
						if(!verificarMateria(&materia_aux))
							imprimir_error("--Clave no registrada en el catalogo de materias--");
						else
							if(!verificarMat_Profe(&materia_aux,&id_aux))
								imprimir_error("--El profesor ingresado no imparte esta materia--");
				}while(materia_aux <= 0 || materia_aux > 50 || !verificarMateria(&materia_aux) ||!verificarMat_Profe(&materia_aux,&id_aux) || !materia);
				ptrgrupo->clave_materia[i] = materia_aux;
				materias[i] = materia_aux;
							
				do
				{
					printf("\nDesea registrar otra materia para este grupo (SI/NO): ");
					fflush(stdin);
					gets(respuesta);
					if(strcmp(respuesta,"SI") != 0 && strcmp(respuesta,"NO") != 0 && strcmp(respuesta,"si") != 0 && strcmp(respuesta,"no") != 0)
						imprimir_error("--Opcion invalida--");
				}while(strcmp(respuesta,"SI") != 0 && strcmp(respuesta,"NO") != 0 && strcmp(respuesta,"si") != 0 && strcmp(respuesta,"no") != 0);
				
				if(i > 5)
						imprimir_error("\t--Solo puede ingresar 6 materias por grupo--");
			}while(strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0 && i <= 5);
			
			do
			{
				printf("\n5) Periodo (1-2):");
				scanf("%d",&ptrgrupo->periodo);
				if(ptrgrupo->periodo <= 0 || ptrgrupo->periodo > 2)
					imprimir_error("--Debe ser 1 o 2--");
			}while(ptrgrupo->periodo <= 0 || ptrgrupo->periodo > 2);
			
			do
			{
				printf("\n6) A%co en que se impartira: ", 164);
				scanf("%d",&ptrgrupo->anio);
				if(ptrgrupo->anio < 2025 || ptrgrupo->anio > 2030)
					imprimir_error("--Fecha invalida--");
			}while(ptrgrupo->anio < 2025 || ptrgrupo->anio > 2030);
			
			ptrgrupo->f_actual.dia = actual->tm_mday;
			ptrgrupo->f_actual.mes = actual->tm_mon + 1;
			ptrgrupo->f_actual.anio = actual->tm_year + 1900;
					
			fseek(f_archivoptr, (ptrgrupo->clave_grupo - 1) * sizeof(struct datosGrupos), SEEK_SET);
			fwrite(&*ptrgrupo, sizeof(struct datosGrupos), 1, f_archivoptr);
		}
		ingresarDatos(respuesta);
	}
	
}

void inscripciones (FILE *f_archivoptr, struct datosInscripcion *inscripcionptr)
{
	FILE  *gruposfile,*profesfile, *materiasfile, *alumnosfile, *foliosfile;
	struct datosGrupos grupo;
	struct datosProfes profe;
	struct datosMaterias materia;
	struct datosAlumnos alumno;
	//struct datosInscripcion inscripcion, *inscripcionptr;
	struct folio folio;
	int  i, id_aux, datosgrupo [2][6] = {0}, id_profe, id_materia;
	char respuesta[3];
	time_t fecha = time(NULL);
	struct tm *actual = localtime(&fecha);
	
	//inscripcionptr = &inscripcion;
	
	ingresarDatos(respuesta);
	
	while(strcmp(respuesta,"SI") == 0 || strcmp(respuesta,"si") == 0)
	{
		if((alumnosfile = fopen("alumnos.dat", "r")) == NULL)
			imprimir_error("No se puede acceder al archivo");
		else
		{
			do
			{
				printf("\n1) Matricula: ");
				scanf("%d",&id_aux);
				fseek(alumnosfile, (id_aux - 1) * sizeof(struct datosAlumnos), SEEK_SET);
				fread(&alumno, sizeof(struct datosAlumnos), 1, alumnosfile);
				if(alumno.matricula != id_aux)
					imprimir_error("--Este alumno no esta registrado--");
				else
					fseek(f_archivoptr, (id_aux - 1) * sizeof(struct datosInscripcion), SEEK_SET);
					fread(&*inscripcionptr, sizeof(struct datosInscripcion), 1, f_archivoptr);
					if(inscripcionptr->matricula != 0)
						imprimir_error("--Este alumno ya esta inscrito--");
			}while(alumno.matricula != id_aux || inscripcionptr->matricula != 0);
			rewind(f_archivoptr);
			inscripcionptr->matricula = id_aux;
			printf("--Nombre del alumno: %s",alumno.nombre);
			fclose(alumnosfile);
		}
		
		if((gruposfile = fopen("grupos.dat", "r")) == NULL)
			imprimir_error("No se puede acceder al archivo");
		else
		{
			if((foliosfile = fopen("folios.dat","r+")) == NULL)
				imprimir_error("No se puede acceder al archivo");
			else
			{
				do
				{
					printf("\n2) Grupo: ");
					scanf("%d",&id_aux);
					fseek(gruposfile, (id_aux - 1) * sizeof(struct datosGrupos), SEEK_SET);
					fread(&grupo, sizeof(struct datosGrupos), 1, gruposfile);
					if(grupo.clave_grupo != id_aux)
						imprimir_error("--Grupo no registrado--");
					else
						fseek(foliosfile, (id_aux - 1) * sizeof(struct folio), SEEK_SET);
						fread(&folio, sizeof(struct folio), 1, foliosfile);
						if(folio.contFolio > 10)
							imprimir_error("--Grupo lleno--");
				}while(grupo.clave_grupo != id_aux || folio.contFolio > 10);
				inscripcionptr->clave_grupo = id_aux;
				folio.contFolio += 1;
				fseek(foliosfile, (id_aux - 1) * sizeof(struct folio), SEEK_SET);
				fwrite(&folio, sizeof(struct folio), 1, foliosfile);				
				inscripcionptr->folio = folio.contFolio;
				
				printf("\n3) Folio: %d", inscripcionptr->folio);
				
				fclose(foliosfile);
			}
			
			for(i = 0; i < 6; i++)
			{
				datosgrupo[0][i] = grupo.ID_empleado[i];
				datosgrupo[1][i] = grupo.clave_materia[i];
			}
			fclose(gruposfile);
		}
		printf("\n3) Folio: %d", inscripcionptr->folio);	
		if((profesfile = fopen("profesores.dat","r")) == NULL)
			imprimir_error("No se puede acceder al archivo");
		else
		{
			
			if((materiasfile = fopen("materias.dat","r")) == NULL)
				imprimir_error("No se puede acceder al archivo");
			else
			{
				printf("\n\n\t\t   DATOS DEL GRUPO: %d\n",inscripcionptr->clave_grupo);
				printf("\n%55s","---------------------------------------------------");
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		    	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE| FOREGROUND_RED | FOREGROUND_INTENSITY );
		    	printf("\n\t%-30s\t%-30s","MATERIA", "PROFESOR");
		    	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
				printf("\n%55s","---------------------------------------------------");
				for(i = 0; i < 6; i++)
				{
					id_profe = datosgrupo[0][i];
					id_materia = datosgrupo[1][i];
										
					if(id_materia != 0)
					{
						fseek(materiasfile, (id_materia - 1) * sizeof(struct datosMaterias), SEEK_SET);
						fread(&materia, sizeof(struct datosMaterias), 1, materiasfile);
						printf("\n\t%-30s",materia.nombre);
						
						fseek(profesfile, (id_profe - 1) * sizeof(struct datosProfes), SEEK_SET);
						fread(&profe, sizeof(struct datosProfes), 1, profesfile);
						printf("\t%-60s",profe.nombre);						
					}
				}
					
				fclose(materiasfile);
			}
			fclose(profesfile);
		}
		
		printf("\n2) Folio: %d", inscripcionptr->folio);
		inscripcionptr->f_actual.dia = actual->tm_mday;
		inscripcionptr->f_actual.mes = actual->tm_mon + 1;
		inscripcionptr->f_actual.anio = actual->tm_year + 1900;
	
		fseek(f_archivoptr, (inscripcionptr->matricula - 1) * sizeof(struct datosInscripcion), SEEK_SET);
		fwrite(&*inscripcionptr, sizeof(struct datosInscripcion), 1, f_archivoptr);		
		printf("\n");
		ingresarDatos(respuesta);
	}
}

void Actualizar_promedio(FILE *f_archivoptr, struct datosAlumnos *ptralumno)
{
	FILE *f_grupos, *f_inscripciones;
	struct datosGrupos grupo;
	struct datosInscripcion inscripcion;
	int grupo_aux, i = 1;
	float calificacion;
	char respuesta[3];
	
	ingresarDatos(respuesta);
	
	while(strcasecmp(respuesta, "SI") == 0)	
	{
		if((f_grupos = fopen("grupos.dat","r")) == NULL)
			imprimir_error("No se puede acceder al archivo");
		else
		{
			printf("1) Grupo: ");
			scanf("%d",&grupo_aux);
			fseek(f_grupos, (grupo_aux - 1) * sizeof(struct datosGrupos), SEEK_SET);
			fread(&grupo, sizeof(struct datosGrupos), 1, f_grupos);
			if(grupo.clave_grupo == 0)
				imprimir_error("--Este grupo no existe--");
			else
			{
				if((f_inscripciones = fopen("inscripcion.dat","r")) == NULL)
					imprimir_error("No se puede acceder al archivo");
				else
				{
					printf("\n\tAlumnos del grupo: %d",grupo.clave_grupo);
					printf("\n%45s\n","****************************************");
					fread(&inscripcion, sizeof(struct datosInscripcion), 1, f_inscripciones);
					while(!feof(f_inscripciones))
					{				
						if(inscripcion.clave_grupo == grupo.clave_grupo)
						{
							fseek(f_archivoptr, (inscripcion.matricula - 1) * sizeof(struct datosAlumnos), SEEK_SET);
							fread(&*ptralumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
							printf("\n\n\tAlumno [%d] %d: %s", i,ptralumno->matricula, ptralumno->nombre);
							do
							{
								printf("\n\tCalificacion: ");
								scanf("%f",&calificacion);
								if(calificacion < 0 || calificacion > 100)
									imprimir_error("--Calificacion invalida (0-100)");
							}while(calificacion < 0 || calificacion > 100);	
							
							ptralumno->promedio = calificacion;
							i++;
							
							fseek(f_archivoptr, (inscripcion.matricula - 1) * sizeof(struct datosAlumnos), SEEK_SET);
							fwrite(&*ptralumno, sizeof(struct datosAlumnos), 1, f_archivoptr);
						}
						fread(&inscripcion, sizeof(struct datosInscripcion), 1, f_inscripciones);
					}
					fclose(f_inscripciones);	
				}	
			}
			fclose(f_grupos);	
		}	
		ingresarDatos(respuesta);	
	}	
}

void Alumnos_por_carrera(FILE *f_archivoptr, struct datosAlumnos *ptralumnor)
{
	
	char carrera[10];
	
			printf("\n*********************************************************\n");
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			printf("\t\t--LISTADO DE CARRERAS--\n");
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			printf("%-40s%-30s\n%-40s%-30s\n%-30s%-30s","LMAD - Multimedia y animacion D.","LA - Actuaria", "LCC - C. Computacionales","LF - Fisica", "LM - Matematicas", "LSTI - Seguridad en TI");
			printf("\n*********************************************************\n");
			do
			{
				printf("\nIngrese la carrera: ");
				fflush(stdin);
				gets(carrera);
				if(!(verificarCarrera(carrera)))
					imprimir_error("--Carrera invalida--");
			}while(!(verificarCarrera(carrera)));
			
			printf("\n\t\tAlumnos de la carrera: %s\n",carrera);
			printf("\n%-10s%-30s%-10s%-10s%-25s%-30s%-10s%-100s","MATRICULA","NOMBRE","CARRERA","SEMESTRE", "NACIMIENTO","CORREO","TELEFONO","DIRECCION");
			fread(&*ptralumnor, sizeof(struct datosAlumnos), 1, f_archivoptr);
			while(!feof(f_archivoptr))
			{	
				if(strcmp(ptralumnor->carrera,carrera) == 0)
				{
					printf("\n%-10d%-30s%-10s%-10d%-5d%-5d%-5d%-30s%-10s%-15s#%-10d%-20s%-15s%-15s",ptralumnor->matricula, ptralumnor->nombre,ptralumnor->carrera,ptralumnor->semestre,
					ptralumnor->fecha_nacimiento.dia,ptralumnor->fecha_nacimiento.mes, ptralumnor->fecha_nacimiento.anio,ptralumnor->correo,
					ptralumnor->telefono,ptralumnor->dir.calle,ptralumnor->dir.numero,ptralumnor->dir.colonia,ptralumnor->dir.municipio,ptralumnor->dir.estado);
				}
					
				fread(&*ptralumnor, sizeof(struct datosAlumnos), 1, f_archivoptr);
			}
			
}

void clases_profe(FILE *f_archivoptr, struct datosGrupos *grupoptr)
{
	FILE *materias;
	struct datosMaterias materia;
	int id_aux,i;
	
	do
	{
		printf("\n-->Clave del profesor: ");
		scanf("%d",&id_aux);
		if(!verificarProfesor(&id_aux))
					imprimir_error("--Este ID no esta registrado--");
	}while(!verificarProfesor(&id_aux));
	
	if((materias = fopen("materias.dat", "r")) == NULL)
			printf("Sin acceso al archivo");
		else{
				
				printf("\n%-10s%-30s%-20s","GRUPO","MATERIA","ID MATERIA");
				printf("\n*********************************************************\n");
				
				fread(&*grupoptr, sizeof(struct datosGrupos), 1, f_archivoptr);
				while(!feof(f_archivoptr))
				{
					for(i = 0; i < 6; i++)
					{
						if(grupoptr->ID_empleado[i] == id_aux)
						{
							fseek(materias, (grupoptr->clave_materia[i] - 1) * sizeof(struct datosMaterias), SEEK_SET);
							fread(&materia, sizeof(struct datosMaterias), 1, materias);
							
							printf("\n%-10d%-30s%-20d",grupoptr->clave_grupo ,materia.nombre,materia.clave_materia);
							
						}
					}
					fread(&*grupoptr, sizeof(struct datosGrupos), 1, f_archivoptr);		
				}
				fclose(materias);
			}
	
	
}

void archivo_alumnos(FILE *f_archivoptr, struct datosAlumnos *alumnoptr)
{
	FILE *escribir;
	
	if((escribir = fopen("alumnos.txt","w")) == NULL)
		printf("\nNo se puede crear el archivo");
	else
	{
		fread(&*alumnoptr, sizeof(struct datosAlumnos), 1 ,f_archivoptr);
		while(!feof(f_archivoptr))
		{
			if(alumnoptr->matricula != 0)
			{
				fprintf(escribir, "%-5d,%-5d,%-15s,%-50s,%-10s,%-50s,%-5.2f,%-30s,%-5d,%-50s,%-50s,%-30s,%-5d,%-5d,%-5d,\n", 
				alumnoptr->matricula,alumnoptr->semestre,alumnoptr->telefono,alumnoptr->nombre,alumnoptr->carrera,
				alumnoptr->correo,alumnoptr->promedio,alumnoptr->dir.calle,alumnoptr->dir.numero,alumnoptr->dir.colonia,alumnoptr->dir.municipio,
				alumnoptr->dir.estado,alumnoptr->fecha_nacimiento.dia,alumnoptr->fecha_nacimiento.mes,alumnoptr->fecha_nacimiento.anio);
			}
			
			fread(&*alumnoptr, sizeof(struct datosAlumnos), 1 ,f_archivoptr);
			
		}
		fclose(escribir);
		printf("\nArchivo creado con exito!");
	}
}

void archivo_profes(FILE *f_archivoptr, struct datosProfes *profeptr)
{
	FILE *escribirfile;
	
	if((escribirfile = fopen("profesores.txt","w")) == NULL)
		printf("\nNo se puede crear el archivo");
	else
	{
		fread(&*profeptr, sizeof(struct datosProfes), 1 ,f_archivoptr);
		while(!feof(f_archivoptr))
		{
			if(profeptr->ID_empleado != 0)
			{
				fprintf(escribirfile, "%-5d,%-5d,%-3d,%-3d,%-3d,%-3d,%-3d,%-3d,%-3d,%-3d,%-3d,%-3d,%-15s,%-50s,%-50s,%-30s,%-3d,%-30s,%-30s,%-30s,%-3d,%-3d,%-3d,\n",
				profeptr->ID_empleado, profeptr->coordinacion, profeptr->clave_materia[0], profeptr->clave_materia[1], profeptr->clave_materia[2],
				profeptr->clave_materia[3], profeptr->clave_materia[4], profeptr->clave_materia[5], profeptr->clave_materia[6], profeptr->clave_materia[7],
				profeptr->clave_materia[8], profeptr->clave_materia[9], profeptr->telefono, profeptr->nombre, profeptr->correo, profeptr->dir.calle,
				profeptr->dir.numero, profeptr->dir.colonia, profeptr->dir.municipio, profeptr->dir.estado, profeptr->fecha_nacimiento.dia,
				profeptr->fecha_nacimiento.mes, profeptr->fecha_nacimiento.anio);
			}
			fread(&*profeptr, sizeof(struct datosProfes), 1 ,f_archivoptr);
		}
		fclose(escribirfile);
		printf("\nArchivo creado con exito!");
	}

}

