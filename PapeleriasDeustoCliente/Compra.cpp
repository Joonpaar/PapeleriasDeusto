#include "Compra.h"
#include "Persona.h"
#include "Material.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

namespace containerCompraCliente{
Compra::Compra() {
	// TODO Auto-generated constructor stub

}

void Compra::verCompra(){
	cout<<"TICKET: "<<ticket<<endl;
	cout<<"PERSONA: "<<p.getNombre()<<endl;
	cout<<"MATERIAL: "<<m.getNom()<<endl;
	cout<<"CANTIDAD: "<<cantidad<<endl;
	cout<<"IMPORTE: "<<importe<<endl;
}

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
}

