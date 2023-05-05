#include "Persona.h"
#include <string.h>
#include <iostream>

using namespace std;

Persona::Persona() {

}

/*void verPersona(const Persona &p){
	cout<<"NOMBRE: "<<p.nombre<<endl;
	cout<<"CONTRASENYA: "<<p.contrasenya<<endl;
}*/

Persona::Persona(char *nom, char *con) {
	this->nombre = new char[strlen(nom) + 1];
	this->nombre = nom;
	this->contrasenya = new char[strlen(con) + 1];
	this->contrasenya = con;

}

Persona::~Persona() {
	delete[]nombre;
	delete[]contrasenya;
}

