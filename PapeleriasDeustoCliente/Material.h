#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "Marca.h"

class Material {
private:
	int unidades;
	char *codigo;
	char *nom;
	float precio;
	char *color;
	Marca m;
public:
	Material();
	Material(int unidades, char *cod, char *nom, float precio, char *color, const Marca &m);
	void verMaterial(const Material &m);
	virtual ~Material();
};

#endif /* MATERIAL_H_ */
