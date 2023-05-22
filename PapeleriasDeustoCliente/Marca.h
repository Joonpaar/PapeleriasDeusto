#ifndef MARCA_H_
#define MARCA_H_

namespace containerMarcaCliente{
class Marca {
private:
	char *nom;
	char *cod;
public:
	Marca();
	Marca(char *nom, char *cod);
	void verMarca();
	virtual ~Marca();
	char* getCod() const;
	void setCod(char *cod);
	char* getNom() const;
	void setNom(char *nom);
};
}
#endif /* MARCA_H_ */
