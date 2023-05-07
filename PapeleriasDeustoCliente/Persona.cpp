#include "Persona.h"
#include <string.h>
#include <iostream>

using namespace std;

namespace containerPersona{
Persona::Persona() {

}

void Persona::verPersona(const Persona &p) {
	cout << "NOMBRE: " << p.nombre << endl;
	cout << "CONTRASENYA: " << p.contrasenya << endl;
}

Persona::Persona(char *nom, char *con) {
	this->nombre = new char[strlen(nom) + 1];
	this->nombre = nom;
	this->contrasenya = new char[strlen(con) + 1];
	this->contrasenya = con;

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

Persona::~Persona() {
	delete[] nombre;
	delete[] contrasenya;
}
}
