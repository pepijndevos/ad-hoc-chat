/*
 * Routing.h
 *
 *  Created on: 9 apr. 2017
 *      Author: Antonis Katzourakis & Eva Knol
 group: 3
 */

#ifndef ROUTING_H_
#define ROUTING_H_

#include<vector>
#include<iostream>

class Routing {
public:
	Routing();
	virtual ~Routing();
	std::vector<int> received_data;

private:
	int incrementSeq(int seq);
	bool isNew();
	void forward();
};

#endif /* ROUTING_H_ */
