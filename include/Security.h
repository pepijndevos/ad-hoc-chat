/*
 * Security.h
 * group: 3
 */

#ifndef SECURITY_H_
#define SECURITY_H_

#include <string>
#include "md5.h"

class Security {
public:
	Security();
    virtual ~Security();

    static std::string getMD5sum(std::string str);
    static std::string getFileMD5(std::string path);

private:
	std::string password;
	void encrypt();
	void decrypt();
};

#endif /* SECURITY_H_ */
