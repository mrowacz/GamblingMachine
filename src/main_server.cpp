/*
 * main.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: mrowacz
 */

#include <thread>
#include <iostream>
#include "GamblingMachine.h"

using namespace std;

int main() {

	game::server s;

	std::cout << "Starting server ..." << std::endl;
	s.run();

	while(true) {}

	return 0;
}





