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
	do {
		/*EMPIEZA EL PROGRAMA DEL SERVIDOR*/
		crearTablas();
		importarDatos();
		char opcion, opcionC, opcionA;
		char nomC[20], conC[20], nomA[20], conA[20];
		int resul;
		do {
			recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
			sscanf(recvBuff, "%c", &opcion);
			switch (opcion) {
			case '1':
				break;
			case '2':
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
					break;
				case '2':
					break;
				case '0':
					break;
				default:
					cout << "No existe opcion" << endl;
				}
				break;
			case '0':
				fin = 1;
				cout << "FIN DE LA CONEXI�N";
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
