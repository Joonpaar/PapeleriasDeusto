#ifndef MATERIAL_H_
#define MATERIAL_H_
#include "Marca.h"

using namespace containerMarca;

namespace containerMaterial{
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
	Material(int unidades, char *cod, char *nom, float precio, char *color,
			const Marca &m);
	void verMaterial(const Material &m);
	char* getCodigo() const;
	void setCodigo(char *codigo);
	char* getColor() const;
	void setColor(char *color);
	const Marca& getM() const;
	void setM(const Marca &m);
	char* getNom() const;
	void setNom(char *nom);
	float getPrecio() const;
	void setPrecio(float precio);
	int getUnidades() const;
	void setUnidades(int unidades);
	virtual ~Material();

		};
}

#endif /* MATERIAL_H_ */
