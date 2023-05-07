#ifndef MARCA_H_
#define MARCA_H_
#include <list>

namespace containerMarca{
class Marca {
private:
	char *nom;
	char *cod;
public:
	Marca();
	Marca(char *nom, char *cod);
	int anyadirMarca(std::list<Marca> &listaMarca, const Marca &m);
	void verMarca(const Marca &m);
	virtual ~Marca();
	char* getCod() const;
	void setCod(char *cod);
	char* getNom() const;
	void setNom(char *nom);
};
}
#endif /* MARCA_H_ */
