#include "Compra.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

Compra::Compra() {
	// TODO Auto-generated constructor stub

}

/*void verCompra(Compra c){
	cout<<"TICKET: "<<c.ticket<<endl;
	cout<<"PERSONA: "<<c.p<<endl;
	cout<<"MATERIAL: "<<c.m<<endl;
	cout<<"CANTIDAD: "<<c.cantidad<<endl;
	cout<<"IMPORTE: "<<c.importe<<endl;
}*/

Compra::Compra(int ticket, const Persona &p, const Material &m, int cantidad, float importe){
	this->ticket = ticket;
	this->p = p;
	this->m = m;
	this->cantidad = cantidad;
	this->importe = importe;
}

Compra::~Compra() {
	// TODO Auto-generated destructor stub
}

