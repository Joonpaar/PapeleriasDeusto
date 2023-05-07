#ifndef PERSONA_H_
#define PERSONA_H_

namespace containerPersonaCliente{
class Persona {private:
	char *nombre;
	char *contrasenya;
public:
	Persona();
	Persona(char *nom, char *con);
	void verPersona(const Persona &p);
	virtual ~Persona();
	char* getContrasenya() const;
	void setContrasenya(char *contrasenya);
	char* getNombre() const;
	void setNombre(char *nombre);
};
}

#endif /* PERSONA_H_ */
