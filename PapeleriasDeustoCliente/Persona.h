#ifndef PERSONA_H_
#define PERSONA_H_

class Persona {private:
	char *nombre;
	char *contrasenya;
public:
	Persona();
	Persona(char *nom, char *con);
	void verPersona(const Persona &p);
	virtual ~Persona();
};

#endif /* PERSONA_H_ */
