#include <stdio.h>
#include "Estructuras.h"

main()
{
	int i;
	struct datosAlumnos blankalumnos = {0,0,"","","",0.0,"","","","",0,0,0,0};
	FILE *ptrarchivo;
	
	if((ptrarchivo = fopen("alumnos.dat","w"))==NULL)
		printf("Error. El archivo no se puede crear");
	else
	{
		for(i = 0; i < 100; i++)
		 fwrite(&blankalumnos, sizeof(struct datosAlumnos), 1, ptrarchivo);
		fclose(ptrarchivo);
	}
}
