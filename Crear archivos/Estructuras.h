#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_


struct direccion
{
	char calle[30], colonia[30], municipio[30], estado[30];
	int numero;
};

struct fecha
{
	int dia, mes, anio;	
};

struct datosAlumnos
{
	int matricula;
	int semestre;
	char telefono[11];
	char nombre[50];
	char carrera[10];
	char correo[50];
	float promedio[10];
	struct direccion dir;
	struct fecha fecha_nacimiento;
};

struct datosProfes
{
	int ID_empleado;
	int coordinacion;
	int clave_materia[10];
	char telefono[11];
	char nombre[50];
	char correo[50];
	struct direccion dir;
	struct fecha fecha_nacimiento;
};

struct datosMaterias
{
	int clave_materia;
	int semestre;
	char nombre[30];
	char descripcion[60];
};

struct datosGrupos
{
	int clave_grupo;
	int semestre;
	int clave_materia[6];
	int ID_empleado[6];
    struct fecha f_actual;
	int periodo;
	int anio;
};

struct datosInscripcion
{
	int folio;
	int matricula;
	int clave_grupo;
	struct fecha f_actual;
};
#endif
