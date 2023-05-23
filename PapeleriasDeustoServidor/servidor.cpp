// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
extern "C" {
#include "bbdd.h"
}

#include <stdio.h>
#include <winsock2.h>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
using namespace std;

float charToFloat(const char *str) {
	char *end;
	float result = strtof(str, &end);
	if (end == str) {
		// La cadena no contiene un número válido
		return 0.0;
	}
	return result;
}

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET conn_socket; //el que lleva la conexion
	SOCKET comm_socket; //el que lo comunica
	struct sockaddr_in server;
	struct sockaddr_in client;
	char sendBuff[512], recvBuff[512]; // lo que yo envio, lo que yo recibo

	printf("\nInitialising Winsock...\n"); // inicializa la libreria
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation creacion del socket( la primera estructura
	if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");
	// cual es la ip y cual es el puerto
	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//BIND (the IP/port with socket)
	if (bind(conn_socket, (struct sockaddr*) &server,
			sizeof(server)) == SOCKET_ERROR) {
		printf("Bind failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	printf("Bind done.\n"); //DEJAR EL SOCKET EN ESPERA

	//LISTEN to incoming connections (socket server moves to listening mode)
	if (listen(conn_socket, 1) == SOCKET_ERROR) {
		printf("Listen failed with error code: %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}

	//ACCEPT incoming connections (server keeps waiting for them)
	printf("Waiting for incoming connections...\n");
	int stsize = sizeof(struct sockaddr);
	comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
	// Using comm_socket is able to send/receive data to/from connected client
	if (comm_socket == INVALID_SOCKET) {
		printf("accept failed with error code : %d", WSAGetLastError());
		closesocket(conn_socket);
		WSACleanup();
		return -1;
	}
	printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr),
			ntohs(client.sin_port));

	// Closing the listening sockets (is not going to be used anymore)
	closesocket(conn_socket);
	int fin = 0;
	crearTablas();
	importarDatos();

	/*or(int i=0;i<5;i++){
	 printf("%s\n",marcas[i]);fflush(stdout);
	 }*/
	char opcion, opcionC, opcionA, opcionA2, opcion2C, opcionA3;
	char nomC[20], conC[20], nomA[20], conA[20];
	char nom[20], con[20], codMat[20], nomMat[20], colorMat[20],
			codMarcaMaterial[10];
	int resul, unidadesMaterial;
	float precioMaterial;

	do {
		/*EMPIEZA EL PROGRAMA DEL SERVIDOR*/
		do {
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff, "%c", &opcion);
			switch (opcion) {
			case '1':
				do {
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					sscanf(recvBuff, "%c", &opcionA);
					switch (opcionA) {
					case '1':
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe el nombre
						sprintf(nomA, "%s", recvBuff);
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe la contrase�a
						sprintf(conA, "%s", recvBuff);
						if (inicioSesionAdmin(nomA, conA) == 1) {
							resul = 1;
							sprintf(sendBuff, "%d", resul);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
							do {
								recv(comm_socket, recvBuff, sizeof(recvBuff),
										0);
								sscanf(recvBuff, "%c", &opcionA2);
								switch (opcionA2) {
								case '1':
									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe el nombre
									sprintf(codMat, "%s", recvBuff);

									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe la contrase�a
									sprintf(nomMat, "%s", recvBuff);

									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe el nombre
									sprintf(colorMat, "%s", recvBuff);

									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe la contrase�a
									sscanf(recvBuff, "%f", &precioMaterial);

									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe el nombre
									sscanf(recvBuff, "%i", &unidadesMaterial);

									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe la contrase�a
									sprintf(codMarcaMaterial, "%s", recvBuff);

									if (comprobacionExiste(codMat, nomMat,
											colorMat, codMarcaMaterial) == 0) {
										anyadirMaterial(codMat, nomMat,
												colorMat, precioMaterial,
												unidadesMaterial,
												codMarcaMaterial);
										resul = 1;
									} else {
										resul = 0;
									}

									sprintf(sendBuff, "%d", resul);
									send(comm_socket, sendBuff,
											sizeof(sendBuff), 0); //Le env�a al cliente 1,2,0

									break;
								case '2':
									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe el nombre
									sprintf(codMat, "%s", recvBuff);
									if (comprobacionExiste(codMat, 0, 0, 0)
											== 1) {
										borrarMaterial(codMat);
										resul = 1;
									} else {
										resul = 0;
									}
									sprintf(sendBuff, "%d", resul);
									send(comm_socket, sendBuff,
											sizeof(sendBuff), 0);
									break;
								case '3':
									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0);
									sprintf(codMat, "%s", recvBuff);

									if (comprobacionExiste(codMat, 0, 0, 0)
											== 1) {
										resul = 1;
									} else {
										resul = 0;
									}
									sprintf(sendBuff, "%d", resul);
									send(comm_socket, sendBuff,
											sizeof(sendBuff), 0); //manda el resul

									if (resul == 1) {
										do {
											recv(comm_socket, recvBuff,
													sizeof(recvBuff), 0);
											sscanf(recvBuff, "%c", &opcionA3);
											switch (opcionA3) {
											case '1':
												recv(comm_socket, recvBuff,
														sizeof(recvBuff), 0);
												sprintf(nomMat, "%s", recvBuff);
												if (editarNombreMaterial(codMat,
														nomMat) == 1) {
													resul = 1;
												} else {
													resul = 0;
												}
												sprintf(sendBuff, "%d", resul);
												send(comm_socket, sendBuff,
														sizeof(sendBuff), 0);
												break;
											case '2':
												recv(comm_socket, recvBuff,
														sizeof(recvBuff), 0);
												sprintf(colorMat, "%s",
														recvBuff);
												if (editarColorMaterial(codMat,
														colorMat) == 1) {
													resul = 1;
												} else {
													resul = 0;
												}
												sprintf(sendBuff, "%d", resul);
												send(comm_socket, sendBuff,
														sizeof(sendBuff), 0);
												break;
											case '3':
												recv(comm_socket, recvBuff,
														sizeof(recvBuff), 0); //Recibe la contrase�a
												sscanf(recvBuff, "%f",
														&precioMaterial);
												if (editarPrecioMaterial(codMat,
														precioMaterial) == 1) {
													resul = 1;
												} else {
													resul = 0;
												}
												sprintf(sendBuff, "%d", resul);
												send(comm_socket, sendBuff,
														sizeof(sendBuff), 0);
												break;
											case '4':
												recv(comm_socket, recvBuff,
														sizeof(recvBuff), 0); //Recibe la contrase�a
												sscanf(recvBuff, "%i",
														&unidadesMaterial);
												if (editarUnidadesMaterial(
														codMat,
														unidadesMaterial)
														== 1) {
													resul = 1;
												} else {
													resul = 0;
												}
												sprintf(sendBuff, "%d", resul);
												send(comm_socket, sendBuff,
														sizeof(sendBuff), 0);
												break;
											case '0':
												break;
											}
										} while (opcionA3 != '0');
										break;
									}
								case '4':
									verMateriales(comm_socket);
									break;
								case '5':
									verCompras(comm_socket);
									break;
								case '6':
									verMarcas(comm_socket);
									break;
								case '7':
									verDatosTienda1(comm_socket);
									verDatosTienda2(comm_socket);
									verDatosTienda3(comm_socket);
									break;
								case '0':
									break;
								}
							} while (opcionA2 != '0');
						} else {
							resul = 0;
							sprintf(sendBuff, "%d", resul);
							send(comm_socket, sendBuff, sizeof(sendBuff), 0);
						}
						break;
					case '2':
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe el nombre
						sprintf(nomA, "%s", recvBuff);
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe la contrase�a
						sprintf(conA, "%s", recvBuff);
						if (registrarUsuario(nomA, conA, 1, getNumPersonas())
								== 1) {
							resul = 1;
						} else {
							resul = 0;
						}
						sprintf(sendBuff, "%d", resul);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0); //Le env�a al cliente 1,2,0
						break;
					case '0':
						break;
					default:
						cout << "No existe opcion" << endl;
						break;
					}
				} while (opcionA != '0');
				break;
			case '2':
				do {
					recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
					sscanf(recvBuff, "%c", &opcionC);
					switch (opcionC) {
					case '1':
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe el nombre
						sprintf(nomC, "%s", recvBuff);
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe la contrase�a
						sprintf(conC, "%s", recvBuff);
						if (inicioSesionCliente(nomC, conC) == 1) {
							resul = 1;
						} else {
							resul = 0;
						}
						sprintf(sendBuff, "%d", resul);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0); //Le env�a al cliente 1,2,0
						if (resul == 1) {
							do {
								recv(comm_socket, recvBuff, sizeof(recvBuff),
										0);
								sscanf(recvBuff, "%c", &opcion2C);
								switch (opcion2C) {
								case '1':
									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0);
									sscanf(recvBuff, "%s", codMat);
									if (comprobacionExiste(codMat, 0, 0, 0)
											== 1) {
										resul = 1;
									} else {
										resul = 0;
									}
									sprintf(sendBuff, "%d", resul);
									send(comm_socket, sendBuff,
											sizeof(sendBuff), 0);

									if (resul == 1) {
										recv(comm_socket, recvBuff,
												sizeof(recvBuff), 0); //Recibe el nombre
										sscanf(recvBuff, "%i",
												&unidadesMaterial);
										if (comprobacionUnidadesExisten(codMat,
												unidadesMaterial) == 1) {
											resul = 1;
											int unidadesAntiguas =
													conseguirUnidadesDelMaterial(
															codMat);
											int unidadesNuevas =
													unidadesAntiguas
															- unidadesMaterial;
											editarUnidadesMaterial(codMat,
													unidadesNuevas);
											float precio =
													conseguirPrecioMaterial(
															codMat);
											float precioAPagar = precio
													* unidadesMaterial;
											anyadirCompra(nomC, codMat,
													unidadesMaterial,
													precioAPagar);
										} else {
											resul = 0;
										}
										sprintf(sendBuff, "%d", resul);
										send(comm_socket, sendBuff,
												sizeof(sendBuff), 0);
									}
									break;
								case '2':
									recv(comm_socket, recvBuff,
											sizeof(recvBuff), 0); //Recibe el nombre
									sscanf(recvBuff, "%s", nom);
									if (compraExiste(nom) == 1) {
										resul = 1;
										sprintf(sendBuff, "%d", resul);
										send(comm_socket, sendBuff,
												sizeof(sendBuff), 0);
										verHistorial1(comm_socket, nom);
										verHistorial2(comm_socket, nom);
										verHistorial3(comm_socket, nom);
									} else {
										resul = 0;
										sprintf(sendBuff, "%d", resul);
										send(comm_socket, sendBuff,
												sizeof(sendBuff), 0);
									}
									break;
								case '3':
									break;
								case '0':
									break;
								}
							} while (opcion2C != '0');
						}
						break;
					case '2':
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe el nombre
						sprintf(nomC, "%s", recvBuff);
						recv(comm_socket, recvBuff, sizeof(recvBuff), 0); //Recibe la contrase�a
						sprintf(conC, "%s", recvBuff);
						if (registrarUsuario(nomC, conC, 0, getNumPersonas())
								== 1) {
							resul = 1;
						} else {
							resul = 0;
						}
						sprintf(sendBuff, "%d", resul);
						send(comm_socket, sendBuff, sizeof(sendBuff), 0); //Le env�a al cliente 1,2,0
						break;
					case '0':
						break;
					default:
						cout << "No existe opcion" << endl;
						break;
					}
				} while (opcionC != '0');
				break;
			case '0':
				fin = 1;
				cout << "FIN DE LA CONEXI�N";
				break;

			default:
				cout << "No existe esta opcion" << endl;
				break;
			}

		} while (opcion != '0');
		guardarDatos();
		borrarDatosTablas();
		/*ACABA EL PROGRAMA DEL SERVIDOR*/

	} while (fin == 0);

	// CLOSING the sockets and cleaning Winsock...
	closesocket(comm_socket);
	WSACleanup();

	return 0;
}
