#ifndef LOGGER_H_
#define LOGGER_H_

class logger {
public:
	logger();
	void mensajeLog(const char * msg);
	void errorLog(const char * msg);
	virtual ~logger();
};

#endif /* LOGGER_H_ */
