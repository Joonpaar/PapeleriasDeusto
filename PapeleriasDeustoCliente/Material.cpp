#include "Material.h"
#include "Marca.h"
#include <string.h>
#include <iostream>

using namespace std;

namespace containerMaterial{
Material::Material() {
	// TODO Auto-generated constructor stub

}

Material::Material(int unidades, char *cod, char *nom, float precio,
		char *color, const Marca &m) {
	this->unidades = unidades;
	this->codigo = new char[strlen(cod) + 1];
	this->codigo = cod;
	this->nom = new char[strlen(nom) + 1];
	this->nom = nom;
	this->precio = precio;
	this->color = new char[strlen(color) + 1];
	this->color = color;
	this->m = m;
}

void Material::verMaterial(const Material &m) {
	cout << "CODIGO: " << m.codigo << endl;
	cout << "NOMBRE: " << m.nom << endl;
	cout << "COLOR: " << m.color << endl;
	cout << "PRECIO: " << m.precio << endl;
	cout << "MARCA: " << m.m.getNom() << endl;
	cout << "UNIDADES: " << m.unidades << endl;
}

char* Material::getCodigo() const {
	return codigo;
}

void Material::setCodigo(char *codigo) {
	this->codigo = codigo;
}

char* Material::getColor() const {
	return color;
}

void Material::setColor(char *color) {
	this->color = color;
}

const Marca& Material::getM() const {
	return m;
}

void Material::setM(const Marca &m) {
	this->m = m;
}

char* Material::getNom() const {
	return nom;
}

void Material::setNom(char *nom) {
	this->nom = nom;
}

float Material::getPrecio() const {
	return precio;
}

void Material::setPrecio(float precio) {
	this->precio = precio;
}

int Material::getUnidades() const {
	return unidades;
}

void Material::setUnidades(int unidades) {
	this->unidades = unidades;
}

Material::~Material() {
	delete[] codigo;
	delete[] color;
	delete[] nom;
}
}
