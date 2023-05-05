#ifndef MARCA_H_
#define MARCA_H_
#include <list>


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
};

#endif /* MARCA_H_ */
