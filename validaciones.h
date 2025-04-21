#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool verificarFecha(int, int, int);
bool bisiesto(int);
bool verificarCorreo(char *);
bool verificarTelefono(char *);

main() 
{
    int dia, mes, anio;
    char correo[100], telefono[50];  

    // Ingresar fecha (DD/MM/AAAA)
    do 
	{
    	printf("Fecha de nacimiento: ");
        scanf("%d/%d/%d", &dia, &mes, &anio);
    } while(!verificarFecha(dia, mes, anio));

    do
    {
    	printf("\nCorreo: "); 
    	fflush(stdin);
    	gets(correo);
    	if(!verificarCorreo(correo))
    	{
    		printf("Correo invalido\n");
		}
	} while(!verificarCorreo(correo));

    do
    {
        printf("\nTelefono: ");
        fgets(telefono, sizeof(telefono), stdin);
        
		size_t len = strlen(telefono);
        if (len > 0 && telefono[len - 1] == '\n') 
        {
            telefono[len - 1] = '\0'; 
        }
		
		 if (!verificarTelefono(telefono))
        {
            printf("Telefono invalido\n");
        }
    } while (!verificarTelefono(telefono));

}

bool verificarFecha(int dia, int mes, int anio) 
{
    bool validar = true;
    int DiasMeses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
     if (anio < 1900 || anio >= 2025) 
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
    {
    	DiasMeses[1] = 29;
	}

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
    int arroba = 0;
    int i;
    char *ultimoPunto = strrchr(correo, '.');

    for (i = 0; correo[i] != '\0'; i++)
    {
        char c = correo[i];

        if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57) || c == 46 || c == 45 || c == 95 || c == 64))
        {
            return false;
        }

        if (c == 64)
        {
            arroba++;
            if (i == 0 || correo[i + 1] == '\0')
                return false;
        }

        if (c == 46 && arroba == 0 && i == 0)
        {
            return false;
        }
    }

    if (arroba != 1)
    {
        return false;
    }

    if (ultimoPunto == NULL || strlen(ultimoPunto) < 3)
    {
        return false;
    }

    return true;
}

bool verificarTelefono(char *telefono)
{
    int i = 0;
    int digitos = 0;

    if (telefono[0] == '+') 
    {
        i = 1;
    }

    while (telefono[i] != '\0') 
    {
        char c = telefono[i];

        if (c >= 48 && c <= 57) 
        {
            digitos++;
        }
        else if (c == 32 || c == 45) 
        {
            
        }
        else 
        {
            return false; 
        }

        i++;
    }

    if (digitos < 7 || digitos > 10) 
    {
        return false;
    }

    return true;
}
