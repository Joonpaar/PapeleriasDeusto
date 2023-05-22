#include "Persona.h"
#include <string.h>
#include <iostream>

using namespace std;

namespace containerPersonaCliente{
Persona::Persona() {

}

void Persona::verPersona() {
	cout << "NOMBRE: " << nombre << endl;
	cout << "CONTRASENYA: " << contrasenya << endl;
}

Persona::Persona(char *nom, char *con) {
	this->nombre = new char[strlen(nom) + 1];
	strcpy(this->nombre , nom);
	this->contrasenya = new char[strlen(con) + 1];
	strcpy(this->contrasenya , con);

}

char* Persona::getContrasenya() const {
	return contrasenya;
}

void Persona::setContrasenya(char *contrasenya) {
	this->contrasenya = contrasenya;
}

char* Persona::getNombre() const {
	return nombre;
}

void Persona::setNombre(char *nombre) {
	this->nombre = nombre;
}

void Usuario::verUsuario(){
	Persona::verPersona();
	cout<<"ID: "<<id<<endl;
}

Persona::~Persona() {
	delete[] nombre;
	delete[] contrasenya;
}
}
