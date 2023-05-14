// IMPORTANT: Winsock Library ("ws2_32") should be linked

#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
using namespace std;

char menu() {
	char opcion;
	cout << "" << endl;
	cout << "1. Admin" << endl;
	cout << "2. Cliente" << endl;
	cout << "0. Salir" << endl;
	cout << "Elige una opcion: ";
	cin >> opcion;
	return opcion;
}

char menuCuentaCliente() {
	char opcion;
	cout << "" << endl;
	cout << "CLIENTE" << endl;
	cout << "1. INICIAR SESION" << endl;
	cout << "2. REGISTRARSE" << endl;
	cout << "0. ATRAS" << endl;
	cout << "Elige una opcion: " << endl;
	cin >> opcion;
	return opcion;
}

char menuCuentaAdmin() {
	char opcion;
	cout << "" << endl;
	cout << "ADMIN" << endl;
	cout << "1. INICIAR SESION" << endl;
	cout << "2. REGISTRARSE" << endl;
	cout << "0. ATRAS" << endl;
	cout << "Elige una opcion: " << endl;
	cin >> opcion;
	return opcion;
}

char menuAdministrador() {
	char opcion;
	cout << "" << endl;
	cout << "MENU ADMINISRADOR" << endl;
	cout << "1. AÑADIR MATERIAL" << endl;
	cout << "2. ELIMINAR MATERIAL" << endl;
	cout << "3. MODIFICAR MATERIAL" << endl;
	cout << "4. VER ITINERARIO" << endl;
	cout << "5. VER TODAS LAS COMPRAS" << endl;
	cout << "6. ANALISIS DE MARCAS" << endl;
	cout << "7. PROXIMAMENTE..." << endl;
	cout << "0. CERRAR SESION" << endl;
	cout << "Elige una opcion: ";
	cin >> opcion;
	return opcion;
}

char menuModificarMaterial() {
	char opcion;
	cout << "" << endl;
	cout << "QUE CARACTERISTICA DESEA MODIFICAR?" << endl;
	cout << "1. NOMBRE" << endl;
	cout << "2. COLOR" << endl;
	cout << "3. PRECIO" << endl;
	cout << "4. UNIDADES" << endl;
	cout << "0. ATRAS" << endl;
	cout << "Elige opcion: " << endl;
	cin >> opcion;
	return opcion;
}

char menuCliente() {
	char opcion;
	cout << "" << endl;
	cout << "MENU CLIENTE" << endl;
	cout << "1. COMPRAR" << endl;
	cout << "2. HISTORIAL" << endl;
	cout << "3. CARRITO" << endl;
	cout << "0. CERRAR SESION" << endl;
	cout << "Elige una opcion: ";
	cin >> opcion;
	return opcion;
}

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	/*
	 * En sendBuff guardaremos lo que el cliente le env�a al servidor
	 * En recvBuff guardaremos lo que el servidor le env�a al cliente
	 * */
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	/*EMPIEZA EL PROGRAMA DEL CLIENTE*/
	char opcion, opcionA, opcionC, opcionC2, opcionA2, opcionA3;
	char nom[20], con[20], codMat[20], nomMat[20], colorMat[20],
			codMarcaMaterial[10];
	int resul, unidadesMaterial;
	float precioMat;
	do {
		opcion = menu();
		sprintf(sendBuff, "%c", opcion);
		send(s, sendBuff, sizeof(sendBuff), 0);
		switch (opcion) {
		case '1':
			do {
				opcionA = menuCuentaAdmin();
				sprintf(sendBuff, "%c", opcionA);
				send(s, sendBuff, sizeof(sendBuff), 0);
				switch (opcionA) {
				case '1':
					cout << "NOMBRE: ";
					cin >> nom;
					cout << "CONTRASENYA: ";
					cin >> con;
					sprintf(sendBuff, "%s", nom);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio el nombre al servidor
					sprintf(sendBuff, "%s", con);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio la contraseña al servidor
					cout << "ENVIO" << endl;
					recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
					sscanf(recvBuff, "%d", &resul);
					cout << "RESULTADO: " << resul << endl;
					if (resul == 1) {
						do {
							opcionA2 = menuAdministrador();
							sprintf(sendBuff, "%c", opcionA2);
							send(s, sendBuff, sizeof(sendBuff), 0);
							switch (opcionA2) {
							case '1':
								cout << "CODIGO DE MATERIAL: ";
								cin >> codMat;
								cout << "NOMBRE: ";
								cin >> nomMat;
								cout << "COLOR: ";
								cin >> colorMat;
								cout << "PRECIO: ";
								cin >> precioMat;
								cout << "UNIDADES: ";
								cin >> unidadesMaterial;
								cout
										<< "CODIGO MARCA (000A/111B/222C/333D/444E): ";
								cin >> codMarcaMaterial;
								sprintf(sendBuff, "%s", codMat);
								send(s, sendBuff, sizeof(sendBuff), 0);
								sprintf(sendBuff, "%s", nomMat);
								send(s, sendBuff, sizeof(sendBuff), 0);
								sprintf(sendBuff, "%s", colorMat);
								send(s, sendBuff, sizeof(sendBuff), 0);
								sprintf(sendBuff, "%.2f", precioMat);
								send(s, sendBuff, sizeof(sendBuff), 0);
								sprintf(sendBuff, "%i", unidadesMaterial);
								send(s, sendBuff, sizeof(sendBuff), 0);
								sprintf(sendBuff, "%s", codMarcaMaterial);
								send(s, sendBuff, sizeof(sendBuff), 0);

								recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
								sscanf(recvBuff, "%d", &resul);
								cout << "RESULTADO : " << resul << endl;
								if (resul == 1) {
									cout << "Producto añadido correctamente!"
											<< endl;
								} else {
									cout << "Error al añadir producto" << endl;
								}
								break;
							case '2':
								cout
										<< "INDIQUE EL CODIGO DE MATERIAL PARA ELIMINAR: "
										<< endl;
								cin >> codMat;

								sprintf(sendBuff, "%s", codMat);
								send(s, sendBuff, sizeof(sendBuff), 0);

								recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
								sscanf(recvBuff, "%d", &resul);
								cout << "RESULTADO : " << resul << endl;

								if (resul == 1) {
									cout << "Producto borrado correctamente!"
											<< endl;
								} else {
									cout << "Error al borrar el producto!"
											<< endl;
								}
								break;
							case '3':
								cout
										<< "INDIQUE EL CODIGO DEL MATERIAL QUE DESEA EDITAR: "
										<< endl;
								cin >> codMat;
								sprintf(sendBuff, "%s", codMat);
								send(s, sendBuff, sizeof(sendBuff), 0);

								recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado
								sscanf(recvBuff, "%d", &resul);
								if (resul == 1) {
									do {
										opcionA3 = menuModificarMaterial();
										sprintf(sendBuff, "%c", opcionA3);
										send(s, sendBuff, sizeof(sendBuff), 0);
										switch (opcionA3) {
										case '1':
											cout << "NOMBRE: ";
											cin >> nomMat;
											sprintf(sendBuff, "%s", nomMat);
											send(s, sendBuff, sizeof(sendBuff),
													0);

											recv(s, recvBuff, sizeof(recvBuff),
													0); //Recibe el resultado del Inicio de Sesion
											sscanf(recvBuff, "%d", &resul);
											cout << resul << endl;
											if (resul == 1) {
												cout
														<< "Nombre del material editado correctamente!"
														<< endl;
											} else {
												cout
														<< "Error al editar el nombre!"
														<< endl;
											}
											break;
										case '2':
											cout << "COLOR: ";
											cin >> colorMat;
											sprintf(sendBuff, "%s", colorMat);
											send(s, sendBuff, sizeof(sendBuff),
													0);

											recv(s, recvBuff, sizeof(recvBuff),
													0); //Recibe el resultado del Inicio de Sesion
											sscanf(recvBuff, "%d", &resul);
											cout << resul << endl;
											if (resul == 1) {
												cout
														<< "Color del material editado correctamente!"
														<< endl;
											} else {
												cout
														<< "Error al editar el color!"
														<< endl;
											}
											break;
										case '3':
											cout << "PRECIO: ";
											cin >> precioMat;
											sprintf(sendBuff, "%.2f",
													precioMat);
											send(s, sendBuff, sizeof(sendBuff),
													0);

											recv(s, recvBuff, sizeof(recvBuff),
													0); //Recibe el resultado del Inicio de Sesion
											sscanf(recvBuff, "%d", &resul);

											if (resul == 1) {
												cout
														<< "Precio del material editado correctamente!"
														<< endl;
											} else {
												cout
														<< "Error al editar el precio!"
														<< endl;
											}
											break;
										case '4':
											cout << "UNIDADES: ";
											cin >> unidadesMaterial;
											sprintf(sendBuff, "%i",
													unidadesMaterial);
											send(s, sendBuff, sizeof(sendBuff),
													0);

											recv(s, recvBuff, sizeof(recvBuff),
													0); //Recibe el resultado del Inicio de Sesion
											sscanf(recvBuff, "%d", &resul);

											if (resul == 1) {
												cout
														<< "Unidades del material editadas correctamente!"
														<< endl;
											} else {
												cout
														<< "Error al editar las unidades!"
														<< endl;
											}
											break;
										case '0':
											cout
													<< "Saliendo del menu de edicion"
													<< endl;
											break;
										}
									} while (opcionA3 != '0');
								} else {
									cout << "Material no existente!" << endl;
								}
								break;
							case '4':
								break;
							case '5':
								break;
							case '6':
								break;
							case '7':
								break;
							case '0':
								cout << "AGUR" << endl;
								break;
							}
						} while (opcionA2 != '0');
					} else {
						cout << "No existe este cliente" << endl;
					}
					break;
				case '2':
					cout << "NOMBRE: ";
					cin >> nom;
					cout << "CONTRASENYA: ";
					cin >> con;
					sprintf(sendBuff, "%s", nom);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio el nombre al servidor
					sprintf(sendBuff, "%s", con);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio la contraseña al servidor

					recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
					sscanf(recvBuff, "%d", &resul);
					cout << "RESULTADO: " << resul << endl;
					if (resul == 1) {
						cout << "Admin Registrado Correctamente!" << endl;
					} else {
						cout << "Error al crear admin!" << endl;
					}
					break;

				case '0':
					break;
				}

			} while (opcionA != '0');
			break;
		case '2':
			do {
				opcionC = menuCuentaCliente();
				sprintf(sendBuff, "%c", opcionC);
				send(s, sendBuff, sizeof(sendBuff), 0);
				switch (opcionC) {
				case '1':
					cout << "NOMBRE: ";
					cin >> nom;
					cout << "CONTRASENYA: ";
					cin >> con;
					sprintf(sendBuff, "%s", nom);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio el nombre al servidor
					sprintf(sendBuff, "%s", con);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio la contraseña al servidor

					recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
					sscanf(recvBuff, "%d", &resul);
					cout << "RESULTADO: " << resul << endl;
					if (resul == 1) {
						do {
							opcionC2 = menuCliente();
							sprintf(sendBuff, "%c", opcionC2);
							send(s, sendBuff, sizeof(sendBuff), 0);
							switch (opcionC2) {
							case '1':
								cout
										<< "INDIQUE EL CODIGO DEL MATERIAL QUE DESEA COMPRAR: "
										<< endl;
								cin >> codMat;
								sprintf(sendBuff, "%s", codMat);
								send(s, sendBuff, sizeof(sendBuff), 0);

								recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
								sscanf(recvBuff, "%d", &resul);
								cout<<"RESULTADO: "<<resul<<endl;
								if (resul == 1) {
									cout
											<< "INDIQUE LA CANTIDAD A COMPRAR DEL MATERIAL "
											<< codMat << ": " << endl;
									cin >> unidadesMaterial;
									sprintf(sendBuff, "%i", unidadesMaterial);
									send(s, sendBuff, sizeof(sendBuff), 0);

									recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
									sscanf(recvBuff, "%d", &resul);

									if(resul == 1){
										cout<<"Material comprado correctamente"<<endl;
									}else{
										cout<<"Error al comprar material"<<endl;
									}
								}
								break;
							case '2':
								break;
							case '3':
								break;
							case '0':
								cout << "Agur" << endl;
							}
						} while (opcionC2 != '0');
					} else {
						cout << "No existe este cliente" << endl;
					}
					break;
				case '2':
					cout << "NOMBRE: ";
					cin >> nom;
					cout << "CONTRASENYA: ";
					cin >> con;
					sprintf(sendBuff, "%s", nom);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio el nombre al servidor
					sprintf(sendBuff, "%s", con);
					send(s, sendBuff, sizeof(sendBuff), 0); //Envio la contraseña al servidor

					recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesion
					sscanf(recvBuff, "%d", &resul);
					cout << "RESULTADO: " << resul << endl;
					if (resul == 1) {
						cout << "Cliente Registrado Correctamente!" << endl;
					} else {
						cout << "Error al crear cliente!" << endl;
					}
					break;

				case '0':
					break;
				}

			} while (opcionC != '0');
			break;
		case '0':
			cout << "AGUR" << endl;
			break;
		default:
			cout << "La opci�n seleccionada no es correcta" << endl;
			break;
		}
	} while (opcion != '0');

	/*ACABA EL PROGRAMA DEL CLIENTE*/
	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
