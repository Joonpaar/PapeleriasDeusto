#ifndef PERSONA_H_
#define PERSONA_H_

namespace containerPersonaCliente {
class Persona {
private:
	char *nombre;
	char *contrasenya;
	int permiso;
public:
	Persona();
	Persona(char *nom, char *con);
	virtual void verPersona();
	virtual ~Persona();
	char* getContrasenya() const;
	void setContrasenya(char *contrasenya);
	char* getNombre() const;
	void setNombre(char *nombre);
};

class Usuario: public Persona {
	int id;
public:
	void verUsuario();
};

}

#endif /* PERSONA_H_ */
