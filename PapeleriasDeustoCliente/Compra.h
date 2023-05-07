#ifndef COMPRA_H_
#define COMPRA_H_
#include "Persona.h"
#include "Material.h"

using namespace containerPersona;
using namespace containerMaterial;

namespace containerCompra{
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
	void verCompra(Compra c);
	virtual ~Compra();
};
}

#endif /* COMPRA_H_ */
