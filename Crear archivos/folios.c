#include <stdio.h>
#include "Estructuras.h"


main()
{
	FILE *archivoptr;
	int i;
	struct folio blankfolio = {0};
	
	if((archivoptr = fopen("folios.dat","w")) == NULL)
		printf("No se puede crear el archivo");
	else
	{
		for(i = 0; i < 20; i++)
			fwrite(&blankfolio, sizeof(struct folio), 1, archivoptr);
		printf("Archivo creado con exito");
		fclose(archivoptr);
	}
	
}
