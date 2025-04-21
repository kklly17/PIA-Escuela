#include <stdio.h>
#include "Estructuras.h"

main()
{
	int i;
	struct datosGrupos blankgrupos = {0,0,{0},{0},0,0,0,0,0};
	FILE *ptrarchivo;
	
	if((ptrarchivo = fopen("grupos.dat","w"))==NULL)
		printf("Error, No se puede crear el archivo");
	else
	{
		for(i = 0; i < 20; i++)
			fwrite(&blankgrupos, sizeof(struct datosGrupos), 1, ptrarchivo);
		fclose(ptrarchivo);
		printf("Archivo creado con exito!!");
	}
}
