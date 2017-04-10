/*
 * Security.h
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef SECURITY_H_
#define SECURITY_H_

#include <string>

class Security {
public:
	Security();
	virtual ~Security();

private:
	std::string password;
	void encrypt();
	void decrypt();
};

#endif /* SECURITY_H_ */
