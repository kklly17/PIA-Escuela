#include <stdio.h>
#include "Estructuras.h"

main()
{
	int i;
	struct datosInscripcion blankinscripcion = {0,0,0,0,0,0};
	FILE *ptrarchivo;
	
	if((ptrarchivo = fopen("inscripcion.dat","w"))==NULL)
		printf("Error, No se puede crear el archivo");
	else
	{
		for(i = 0; i < 100; i++)
			fwrite(&blankinscripcion, sizeof(struct datosInscripcion), 1, ptrarchivo);
		fclose(ptrarchivo);
		printf("Archivo creado con exito!!");
	}
}
