#include "bbdd.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sqlite3.h"

//CREACION DE TABLAS Y FUNCIONES DE MENU

int crearTablaMarca() {
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	char *sql =
			"CREATE TABLE IF NOT EXISTS marca (cod_marca STRING PRIMARY KEY, nombre TEXT);";

	char *errmsg = NULL;
	rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "No se pudo crear la tabla: %s\n", errmsg);
		sqlite3_free(errmsg);
	} else {
		printf("Tabla marca creada correctamente.\n");
	}
	sqlite3_close(db);
	return 0;
}

int importarMarcas() {
	FILE *pf;
	char *codigo = malloc(sizeof(char) * 20);
	char *nombre = malloc(sizeof(char) * 20);

	char sql[200];
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	pf = fopen("Marcas.txt", "r");
	if (pf != (FILE*) NULL) {
		while (fscanf(pf, "%s %s", codigo, nombre) != EOF) {
			sprintf(sql, "INSERT INTO marca VALUES('%s','%s')", codigo, nombre);
			char *errmsg = NULL;
			rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "No se pudo insertar en la tabla: %s\n",
						errmsg);
				sqlite3_free(errmsg);
			} else {
				printf("Se ha insertado correctamente.\n");
			}
		}
		fclose(pf);
	}

	sqlite3_close(db);
	free(codigo);
	free(nombre);
	return 0;

}

int crearTablaMateriales() {
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	char *sql =
			"CREATE TABLE IF NOT EXISTS material (cod_material STRING PRIMARY KEY, nombre_material TEXT NOT NULL, color TEXT, precio FLOAT, unidades INT, cod_marca STRING, FOREIGN KEY (cod_marca) REFERENCES marca(cod_marca));";

	char *errmsg = NULL;
	rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "No se pudo crear la tabla: %s\n", errmsg);
		sqlite3_free(errmsg);
	} else {
		printf("Tabla material  creada correctamente.\n");
	}
	sqlite3_close(db);
	return 0;
}

int importarMateriales() {
	FILE *pf;
	char *codigo = malloc(sizeof(char) * 20);
	char *nombre = malloc(sizeof(char) * 30);
	char *color = malloc(sizeof(char) * 20);
	float precio;
	int unidades;
	char *codigoMarca = malloc(sizeof(char) * 20);
	char sql[200];
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	pf = fopen("Materiales.txt", "r");
	if (pf != (FILE*) NULL) {
		while (fscanf(pf, "%s %s %s %f %i %s", codigo, nombre, color, &precio,
				&unidades, codigoMarca) != EOF) {
			sprintf(sql,
					"INSERT INTO material VALUES ('%s', '%s', '%s', %.2f, %i, '%s')",
					codigo, nombre, color, precio, unidades, codigoMarca);
			char *errmsg = NULL;
			rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "No se pudo insertar en la tabla: %s\n",
						errmsg);
				sqlite3_free(errmsg);
			} else {
				printf("Se ha insertado correctamente.\n");
			}
		}
		fclose(pf);
	}

	sqlite3_close(db);
	free(codigo);
	free(nombre);
	free(color);
	free(codigoMarca);
	return 0;

}

int crearTablaPersona() {
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	char *sql =
			"CREATE TABLE IF NOT EXISTS persona(nombre STRING PRIMARY KEY, contrasenya TEXT, permiso INT, id INT);";

	char *errmsg = NULL;
	rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "No se pudo crear la tabla: %s\n", errmsg);
		sqlite3_free(errmsg);
	} else {
		printf("Tabla persona creada correctamente.\n");
	}
	sqlite3_close(db);
	return 0;
}

int importarPersonas() {
	FILE *pf;
	char *nombre = malloc(sizeof(char) * 30);
	char *contrasenya = malloc(sizeof(char) * 30);
	int permiso, id;
	char sql[200];
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	pf = fopen("Personas.txt", "r");
	if (pf != (FILE*) NULL) {
		while (fscanf(pf, "%s %s %i %i", nombre, contrasenya, &permiso, &id)
				!= EOF) {
			sprintf(sql, "INSERT INTO persona VALUES ('%s', '%s', %i, %i)",
					nombre, contrasenya, permiso, id);
			char *errmsg = NULL;
			rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "No se pudo insertar en la tabla: %s\n",
						errmsg);
				sqlite3_free(errmsg);
			} else {
				printf("Se ha insertado correctamente.\n");
			}
		}
		fclose(pf);
	}

	sqlite3_close(db);
	free(nombre);
	free(contrasenya);
	return 0;

}

int crearTablaCompra() {
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	char *sql =
			"CREATE TABLE IF NOT EXISTS compra(ticket INT PRIMARY KEY, nombre_persona TEXT, cod_material TEXT, cantidad INT, importe FLOAT, FOREIGN KEY (nombre_persona) REFERENCES persona(nombre), FOREIGN KEY (cod_material) REFERENCES material(cod_material));";

	char *errmsg = NULL;
	rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "No se pudo crear la tabla: %s\n", errmsg);
		sqlite3_free(errmsg);
	} else {
		printf("Tabla compra creada correctamente.\n");
	}
	sqlite3_close(db);
	return 0;
}

int importarCompras() {
	FILE *pf;
	int ticket;
	char *nombreProducto = malloc(sizeof(char) * 20);
	char *codigoMarca = malloc(sizeof(char) * 20);
	int cantidad;
	float importe;
	char sql[200];
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	pf = fopen("Compras.txt", "r");
	if (pf != (FILE*) NULL) {
		while (fscanf(pf, "%i %s %s %i %f", &ticket, nombreProducto,
				codigoMarca, &cantidad, &importe) != EOF) {
			sprintf(sql, "INSERT INTO compra VALUES (%i, '%s', '%s', %i , %f)",
					ticket, nombreProducto, codigoMarca, cantidad, importe);
			char *errmsg = NULL;
			rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
			if (rc != SQLITE_OK) {
				fprintf(stderr, "No se pudo insertar en la tabla: %s\n",
						errmsg);
				sqlite3_free(errmsg);
			} else {
				printf("Se ha insertado correctamente.\n");
			}
		}
		fclose(pf);
	}

	sqlite3_close(db);
	free(nombreProducto);
	free(codigoMarca);
	return 0;

}

int registrarUsuario(char *nombre, char *contrasenya, int permiso) {
	sqlite3 *db;
	int rc = sqlite3_open("Datos.sqlite", &db);
	if (rc) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}
	char sql[200];
	sprintf(sql, "INSERT INTO persona VALUES ('%s', '%s', %i)", nombre,
			contrasenya, permiso);

	char *errmsg = NULL;
	rc = sqlite3_exec(db, sql, NULL, 0, &errmsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "No se pudo insertar en la tabla: %s\n", errmsg);
		sqlite3_free(errmsg);
	} else {
		printf("Se ha insertado correctamente.\n");
	}
	sqlite3_close(db);
	return 0;
}

int inicioSesionAdmin(char *nombre, char *contrasenya) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	sprintf(sql,
			"SELECT * FROM persona WHERE nombre = '%s' AND contrasenya = '%s' AND permiso = 1",
			nombre, contrasenya);
	result = sqlite3_open("Datos.sqlite", &db);

	if (result != SQLITE_OK) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt); //Cerrar la sentencia
		sqlite3_close(db);
		return 1;
	}
	return 0;

}

int inicioSesionCliente(char *nombre, char *contrasenya) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	sprintf(sql,
			"SELECT * FROM persona WHERE nombre = '%s' AND contrasenya = '%s' AND permiso = 0",
			nombre, contrasenya);
	result = sqlite3_open("Datos.sqlite", &db);

	if (result != SQLITE_OK) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt); //Cerrar la sentencia
		sqlite3_close(db);
		return 1;
	}
	return 0;

}

int anyadirMaterial(char *codigo, char *nombre, char *color, float precio,
		int unidades, char *codigoMarca) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql,
			"INSERT INTO material VALUES ('%s', '%s', '%s', %.2f, %i, '%s')",
			codigo, nombre, color, precio, unidades, codigoMarca);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int borrarMaterial(char *cod_material) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "delete from material where cod_material = '%s'",
			cod_material);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int editarNombreMaterial(char *codigo_material, char *nombre) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql,
			"UPDATE material SET nombre_material = '%s' WHERE cod_material = '%s'",
			nombre, codigo_material);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int editarColorMaterial(char *codigo_material, char *color) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "UPDATE material SET color = '%s' WHERE cod_material = '%s'",
			color, codigo_material);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int editarPrecioMaterial(char *codigo_material, float precio) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql,
			"UPDATE material SET precio = '%.2f' WHERE cod_material = '%s'",
			precio, codigo_material);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int editarUnidadesMaterial(char *codigo_material, int unidades) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql,
			"UPDATE material SET unidades = '%i' WHERE cod_material = '%s'",
			unidades, codigo_material);
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int verMateriales() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	char cod_material[10], nombre[20], color[20], cod_marca[10];
	float precio;
	int unidades;
	result = sqlite3_open("Datos.sqlite", &db);

	sprintf(sql, "select * from material");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	while (result == SQLITE_ROW) {
		sprintf(cod_material, "%s", (char*) sqlite3_column_text(stmt, 0));
		sprintf(nombre, "%s", (char*) sqlite3_column_text(stmt, 1));
		sprintf(color, "%s", (char*) sqlite3_column_text(stmt, 2));
		precio = (float) sqlite3_column_double(stmt, 3);
		unidades = sqlite3_column_int(stmt, 4);
		sprintf(cod_marca, "%s", (char*) sqlite3_column_text(stmt, 5));
		printf(
				"MATERIAL: %s - NOMBRE: %s - COLOR: %s - PRECIO: %.2f - UNIDADES: %i - MARCA: %s\n",
				cod_material, nombre, color, precio, unidades, cod_marca);
		result = sqlite3_step(stmt); //Ejecutar la sentencia
	}
	sqlite3_finalize(stmt); //Cerrar la sentencia

	return 0;

}

int verCompras() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	char cod_material[10], nombre_persona[20];
	float importe;
	int unidades, ticket;
	result = sqlite3_open("Datos.sqlite", &db);

	sprintf(sql, "select * from compra");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	while (result == SQLITE_ROW) {
		ticket = sqlite3_column_int(stmt, 0);
		sprintf(nombre_persona, "%s", (char*) sqlite3_column_text(stmt, 1));
		sprintf(cod_material, "%s", (char*) sqlite3_column_text(stmt, 2));
		unidades = sqlite3_column_int(stmt, 3);
		importe = (float) sqlite3_column_double(stmt, 4);
		printf(
				"TICKET: %i - CLIENTE: %s - MATERIAL: %s - UNIDADES: %i - IMPORTE: %.2f \n",
				ticket, nombre_persona, cod_material, unidades, importe);
		result = sqlite3_step(stmt); //Ejecutar la sentencia
	}
	sqlite3_finalize(stmt); //Cerrar la sentencia

	return 0;

}

int crearTablas() {
	crearTablaMarca();
	crearTablaMateriales();
	crearTablaPersona();
	crearTablaCompra();
	return 0;
}

int importarDatos() {
	importarMarcas();
	importarMateriales();
	importarCompras();
	importarPersonas();
	return 0;
}

//BORRADO DE DATOS

int borrarDatosMateriales() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "delete from material");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int borrarDatosCompras() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "delete from compra");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int borrarDatosPersonas() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "delete from persona");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int borrarDatosMarca() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "delete from marca");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int borrarDatosTablas() {
	borrarDatosCompras();
	borrarDatosMarca();
	borrarDatosMateriales();
	borrarDatosPersonas();
	return 0;
}

//COMPARAR COSAS

int comprobacionExiste(char *codigo, char *nombre, char *color,
		char *codigoMarca) {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	sprintf(sql,
			"SELECT * FROM material WHERE cod_material = '%s' OR nombre_material = '%s' AND color = '%s' AND cod_marca = '%s'",
			codigo, nombre, color, codigoMarca);
	result = sqlite3_open("Datos.sqlite", &db);

	if (result != SQLITE_OK) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt); //Cerrar la sentencia
		sqlite3_close(db);
		return 1; //EXISTE
	}
	return 0; //NO EXISTE

}

int datosMaterialesExisten() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	sprintf(sql, "SELECT * FROM material");
	result = sqlite3_open("Datos.sqlite", &db);

	if (result != SQLITE_OK) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt); //Cerrar la sentencia
		sqlite3_close(db);
		return 1;
	}
	return 0;

}

int datosComprasExisten() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	sprintf(sql, "SELECT * FROM compra");
	result = sqlite3_open("Datos.sqlite", &db);

	if (result != SQLITE_OK) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt); //Cerrar la sentencia
		sqlite3_close(db);
		return 1;
	}
	return 0;

}

int datosMarcasExisten() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	char sql[200];
	int result;
	sprintf(sql, "SELECT * FROM marca");
	result = sqlite3_open("Datos.sqlite", &db);

	if (result != SQLITE_OK) {
		fprintf(stderr, "No se pudo abrir la base de datos: %s\n",
				sqlite3_errmsg(db));
		sqlite3_close(db);
		return -1;
	}
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL); //Preparar la sentencia
	result = sqlite3_step(stmt); //Ejecutar la sentencia
	if (result == SQLITE_ROW) {
		sqlite3_finalize(stmt); //Cerrar la sentencia
		sqlite3_close(db);
		return 1;
	}
	return 0;

}

//GUARDADO

int guardarDatosPersonas() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "select * from persona");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	FILE *f = fopen("Personas.txt", "w"); // Abre el archivo para escritura y borra el contenido previo
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		fprintf(f, "%s %s %i", sqlite3_column_text(stmt, 0),
				sqlite3_column_text(stmt, 1), sqlite3_column_int(stmt, 2));
	}
	fclose(f);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int guardarDatosMateriales() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "select * from material");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	FILE *f = fopen("Materiales.txt", "w"); // Abre el archivo para escritura y borra el contenido previo
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		fprintf(f, "%s %s %s %f %i %s\n", sqlite3_column_text(stmt, 0),
				sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2),
				sqlite3_column_double(stmt, 3), sqlite3_column_int(stmt, 4),
				sqlite3_column_text(stmt, 5));
	}
	fclose(f);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int guardarDatosCompras() {
	sqlite3 *db;
	sqlite3_stmt *stmt;
	int result;
	char sql[200];
	//Establecer la conexión con la bb
	result = sqlite3_open("Datos.sqlite", &db);
	if (result != SQLITE_OK) {
		printf("Error al abrir la BBDD\n");
		fflush(stdout);
		return result;
	}
	sprintf(sql, "select * from compra");
	sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);

	FILE *f = fopen("Compras.txt", "w"); // Abre el archivo para escritura y borra el contenido previo
	while (sqlite3_step(stmt) == SQLITE_ROW) {
		fprintf(f, "%i %s %s %i %f", sqlite3_column_int(stmt, 0),
				sqlite3_column_text(stmt, 1), sqlite3_column_text(stmt, 2),
				sqlite3_column_int(stmt, 3), sqlite3_column_double(stmt, 4));
	}
	fclose(f);

	sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	return 0;
}

int guardarDatos() {
	guardarDatosCompras();
	guardarDatosMateriales();
	guardarDatosPersonas();
	return 0;
}
