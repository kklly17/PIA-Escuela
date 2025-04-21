#include <stdio.h>
//#include "validaciones.h"
#include "Estructuras.h"

void alumnos (FILE *, struct datosAlumnos *ptralumno);


void alumnos(FILE *f_archivoptr, struct datosAlumnos *ptralumno)
{
	//struct datosAlumnos alumno;
	//struct datosAlumnos *ptralumno;
	
	//ptralumno = &alumno;
	
	printf("Ingrese la matricula: ");
	scanf("%d", &ptralumno->matricula);
	
	printf("\nla matricula es: %d ",ptralumno->matricula);
}
