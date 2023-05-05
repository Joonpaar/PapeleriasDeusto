#include "Material.h"
#include <string.h>
#include <iostream>

using namespace std;

Material::Material() {
	// TODO Auto-generated constructor stub

}

Material::Material(int unidades, char *cod, char *nom, float precio, char *color, const Marca &m){
	this->unidades = unidades;
	this->codigo = new char[strlen(cod)+1];
	this->codigo = cod;
	this->nom = new char[strlen(nom)+1];
	this->nom = nom;
	this->precio = precio;
	this->color = new char[strlen(color)+1];
	this->color = color;
	this->m = m;
}

/*void verMaterial(const Material &m){
	cout<<"CODIGO: "<<m.codigo<<endl;
	cout<<"NOMBRE: "<<m.nom<<endl;
	cout<<"COLOR: "<<m.color<<endl;
	cout<<"PRECIO: "<<m.precio<<endl;
	cout<<"MARCA: "<<m.m<<endl;
	cout<<"UNIDADES: "<<m.unidades<<endl;
}*/

Material::~Material() {
	delete[]codigo;
	delete[]color;
	delete[]nom;
}
