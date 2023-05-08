#ifndef BBDD_H_
#define BBDD_H_

//CREACION TABLAS
int crearTablaCompra();
int crearTablaPersona();
int crearTablaMarca();
int crearTablaMateriales();
int crearTablas();

//MENU ADMIN
int registrarUsuario(char *nombre, char *contrasenya, int permiso);
int inicioSesionAdmin(char *nombre, char *contrasenya);
int inicioSesionCliente(char *nombre, char *contrasenya);

//MENU MATERIALES
int anyadirMaterial(char *codigo, char *nombre, char *color, float precio, int unidades, char *codigoMarca);
int borrarMaterial(char *codigo_material);
int editarNombreMaterial(char *codigo_material, char *nombre);
int editarColorMaterial(char *codigo_material, char *color);
int editarPrecioMaterial(char *codigo_material, float precio);
int editarUnidadesMaterial(char *codigo_material, int unidades);
int verMateriales();
int verCompras();
int verMarcas();

//DATOS
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
int datosMaterialesExisten();
int datosComprasExisten();
int datosMarcasExisten();

//GUARDADO DE DATOS
int guardarDatosPersonas();
int guardarDatosMateriales();
int guardarDatosCompras();
int guardarDatos();

#endif
