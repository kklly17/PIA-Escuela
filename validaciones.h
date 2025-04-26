#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool verificarFecha(int, int, int);
bool bisiesto(int);
bool verificarCorreo(char *);
bool verificarTelefono(char *);
bool verificarNombre(char *);
bool verificarCarrera(char *);
bool verificarDescripcion(char *);


bool verificarFecha(int dia, int mes, int anio) 
{
    bool validar = true;
    int DiasMeses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
     if (anio < 1950 || anio >= 2010) 
	{
        validar = false;
        printf("El anio no existe\n");
    }
    
    if (mes < 1 || mes > 12) 
	{
        validar = false;
        printf("El mes no existe\n");
    }
    if (mes == 2 && bisiesto(anio))
    	DiasMeses[1] = 29;

    if (dia < 1 || dia > DiasMeses[mes - 1]) 
	{
        validar = false;
        printf("El dia no existe\n");
    }

    return validar;
}

bool bisiesto(int anio) 
{
    return (anio % 4 == 0 && (anio % 100 != 0 || anio % 400 == 0));
}

bool verificarCorreo(char *correo)
{
    int arroba = 0, i = 0; 
    char *ultimoPunto = strrchr(correo, '.');
    bool validar = true;

    for (i = 0; correo[i] != '\0'; i++)
    {
        char c = correo[i];

        if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 46 || c == 45 || c == 95 || c == 64))
            validar = false;

        if (c == 64)
        {
            arroba++;
            if (i == 0 || correo[i + 1] == '\0')
                return false;
        }

        if (c == 46 && arroba == 0 && i == 0)
            validar = false;
    }

    if (arroba != 1)
        validar = false;

    if (ultimoPunto == NULL || strlen(ultimoPunto) < 3)
        validar = false;

    return validar;
}

bool verificarTelefono(char *telefono)
{
    int i = 0, digitos = 0;
    bool verificar = true;

    if (telefono[0] == '+') 
        i = 1;
        
    while (telefono[i] != '\0') 
    {
        if(isdigit(telefono[i]))
			digitos++; 
		else if (telefono[i] != 32 && telefono[i] != '-')
             verificar = false;
        i++;
    }
    if (digitos < 10 || digitos > 12) 
        verificar = false;

    return verificar;
}

bool verificarNombre(char *nombrePTR)
{
	int i = 0, longitud = strlen(nombrePTR);
	bool validar = true;
	
	while(*(nombrePTR + i) != '\0')
	{
		if(longitud = 1 &&*(nombrePTR + 0) == 32)
			validar = false;
		  
		if(!(*(nombrePTR + i) >= 65 && *(nombrePTR + i) <= 90 || *(nombrePTR + i) >= 97 && *(nombrePTR + i) <= 122 || *(nombrePTR + i) == 32))
		 	validar = false;
		i++;
	}
	return validar;
}

bool verificarCarrera(char *carreraPTR)
{
	bool validar = true;
	int i = 0;
	
	while(carreraPTR[i] != '\0')
	{
		if(carreraPTR[i] >= 97 && carreraPTR[i] <= 122)
			carreraPTR[i] -=32;
		i++;
	}
	
	if(!(strcmp(carreraPTR,"LMAD") == 0 || strcmp(carreraPTR,"LA") == 0 || strcmp(carreraPTR,"LCC") == 0
		|| strcmp(carreraPTR,"LF") == 0 || strcmp(carreraPTR,"LM") == 0 || strcmp(carreraPTR,"LSTI") == 0))
		validar = false;
	return validar;	
}

bool verificarDescripcion(char *descripcionPTR)
{
	int i = 0, longitud = strlen(descripcionPTR);
	bool validar = true;
	
	while(*(descripcionPTR + i) != '\0')
	{
		if(longitud = 1 && *(descripcionPTR + 0) == 32)
			validar = false;
		  
		if(!(*(descripcionPTR + i) >= 65 && *(descripcionPTR + i) <= 90 || *(descripcionPTR + i) >= 97 && *(descripcionPTR + i) <= 122 
		|| *(descripcionPTR + i) == 32 || *(descripcionPTR + i) >= 48 && *(descripcionPTR + i) <= 57 || *(descripcionPTR + i) == 46
		|| *(descripcionPTR + i) == 44))
		 	validar = false;
		i++;
	}
	return validar;
}
