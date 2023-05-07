#include "Marca.h"
#include <string.h>
#include <iostream>

using namespace std;
namespace containerMarca{
Marca::Marca() {
	// TODO Auto-generated constructor stub

}

Marca::Marca(char *nom, char *cod) {
	this->cod = new char[strlen(cod) + 1];
	this->cod = cod;
	this->nom = new char[strlen(nom) + 1];
	this->nom = nom;
}

void anyadirMarca(std::list<Marca> &listaMarca, const Marca &m) {
	listaMarca.push_back(m);
}

void Marca::verMarca(const Marca &m) {
	cout << "CODIGO: " << m.cod << endl;
	cout << "NOMBRE: " << m.nom << endl;
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

