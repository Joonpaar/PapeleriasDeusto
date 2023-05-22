#include "Marca.h"
#include <string.h>
#include <iostream>

using namespace std;
namespace containerMarcaCliente{
Marca::Marca() {
	// TODO Auto-generated constructor stub

}

Marca::Marca(char *nom, char *cod) {
	this->cod = new char[strlen(cod) + 1];
	strcpy(this->cod , cod);
	this->nom = new char[strlen(nom) + 1];
	strcpy(this->nom , nom);
}

void Marca::verMarca() {
	cout << "CODIGO: " << cod << endl;
	cout << "NOMBRE: " << nom << endl;
}

char* Marca::getCod() const {
	return this->cod;
}

void Marca::setCod(char *cod) {
	this->cod = cod;
}

char* Marca::getNom() const {
	return nom;
}

void Marca::setNom(char *nom) {
	this->nom = nom;
}

Marca::~Marca() {
	delete[] cod;
	delete[] nom;
}
}

