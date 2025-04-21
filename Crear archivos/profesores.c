#include <stdio.h>
#include "Estructuras.h"

main()
{
	int i;
	struct datosProfes blankprofes = {0,0,{0},"","","","","","","",0,0,0,0};
	FILE *ptrarchivo;
	
	
	if((ptrarchivo = fopen("profesores.dat","w"))==NULL)
		printf("Error. El archivo no se puede crear");
	else
	{
		for(i=0; i < 50; i++)
			fwrite(&blankprofes, sizeof(struct datosProfes), 1, ptrarchivo);
		fclose(ptrarchivo);
		printf("Archivo creado con exito");
	}
}
