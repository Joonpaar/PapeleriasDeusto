#ifndef BBDD_H_
#define BBDD_H_

#include "persona.h"
#include "material.h"

//CREACION TABLAS
int crearTablaCompra();
int crearTablaPersona();
int crearTablaMarca();
int crearTablaMateriales();
int crearTablas();

//MENU ADMIN
int registrarUsuario(Persona p);
int inicioSesionAdmin(Persona p);

//MENU MATERIALES
int anyadirMaterial(Material m);
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
int comprobacionExiste(Material m);
int datosMaterialesExisten();
int datosComprasExisten();
int datosMarcasExisten();

//GUARDADO DE DATOS
int guardarDatosPersonas();
int guardarDatosMateriales();
int guardarDatosCompras();
int guardarDatos();

#endif
