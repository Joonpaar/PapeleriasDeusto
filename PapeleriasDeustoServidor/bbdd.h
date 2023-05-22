#ifndef BBDD_H_
#define BBDD_H_


#include <winsock2.h>

//CREACION TABLAS
int crearTablaCompra();
int crearTablaPersona();
int crearTablaMarca();
int crearTablaMateriales();
int crearTablas();

//MENU ADMIN
int registrarUsuario(char *nombre, char *contrasenya, int permiso, int id);
int inicioSesionAdmin(char *nombre, char *contrasenya);
int inicioSesionCliente(char *nombre, char *contrasenya);
int verMateriales(SOCKET comm_socket);
int verCompras(SOCKET comm_socket);
int verMarcas(SOCKET comm_socket);
int verDatosTienda1(SOCKET comm_socket);
int verDatosTienda2(SOCKET comm_socket);
int verDatosTienda3(SOCKET comm_socket);

//MENU MATERIALES
int anyadirMaterial(char *codigo, char *nombre, char *color, float precio, int unidades, char *codigoMarca);
int borrarMaterial(char *codigo_material);
int editarNombreMaterial(char *codigo_material, char *nombre);
int editarColorMaterial(char *codigo_material, char *color);
int editarPrecioMaterial(char *codigo_material, float precio);
int editarUnidadesMaterial(char *codigo_material, int unidades);

//MENU CLIENTE
int conseguirUnidadesDelMaterial(char* codigo);
int anyadirCompra(char* nombrePersona, char* codigoMat, int cantidad, float importe);
float conseguirPrecioMaterial(char *codigoMat);
int verHistorial1(SOCKET comm_socket, char* nomPersona);
int verHistorial2(SOCKET comm_socket, char* nomPersona);
int verHistorial3(SOCKET comm_socket, char *nomPersona);

//DATOS
void cargarMarcas(char marcas[][50]);
int importarMarcas();
int importarCompras();
int importarPersonas();
int importarMateriales();
int importarDatos();
//BORRADO DE TABLAS
int borrarDatosMateriales();
int borrarDatosCompras();
int borrarDatosPersonas();
int borrarDatosMarcas();
int borrarDatosTablas();

//COMPROBACIONES EN TABLAS
int comprobacionExiste(char *codigo, char *nombre, char *color, char *codigoMarca);
int comprobacionUnidadesExisten(char *codigo, int unidades);
int datosMaterialesExisten();
int datosComprasExisten();
int datosMarcasExisten();
int getNumPersonas();

//GUARDADO DE DATOS
int guardarDatosPersonas();
int guardarDatosMateriales();
int guardarDatosCompras();
int guardarDatos();

#endif
