#ifndef COMPRA_H_
#define COMPRA_H_
#include "Persona.h"
#include "Material.h"

using namespace containerPersonaCliente;
using namespace containerMaterialCliente;

namespace containerCompraCliente{
class Compra {
private:
	int ticket;
	Persona p;
	Material m;
	int cantidad;
	float importe;
public:
	Compra();
	Compra(int ticket, const Persona &p, const Material &m, int cantidad, float importe);
	void verCompra();
	virtual ~Compra();
};
}

#endif /* COMPRA_H_ */
