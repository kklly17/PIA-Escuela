#include <stdio.h>
#include "Estructuras.h"

main()
{
	int i;
	struct datosMaterias blankmaterias = {0,0,"",""};
	FILE *ptrarchivo;
	
	if((ptrarchivo = fopen("materias.dat","w"))==NULL)
		printf("Error, No se puede crear el archivo");
	else
	{
		for(i = 0; i < 50; i++)
			fwrite(&blankmaterias, sizeof(struct datosMaterias), 1, ptrarchivo);
		fclose(ptrarchivo);
		printf("Archivo creado con exito!!");
	}
}
