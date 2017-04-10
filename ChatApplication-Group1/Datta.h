/*
 * Data.h
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef DATTA_H_
#define DATTA_H_

#include <vector>
#include <string>

class Datta {
public:
	Datta();
	virtual ~Datta();
	std::vector<std::string> datta;
	void loadData();
	void loadFile();
	void createHash();

private:
	void convertData();

};

#endif /* DATTA_H_ */
