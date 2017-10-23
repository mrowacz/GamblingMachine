/*
 * main.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: mrowacz
 */

#include <chrono>
#include <thread>
#include <iostream>
#include "GamblingMachine.h"

using namespace std;

int main()
{
	game::client c;

	std::system("./server &");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::cout << "Starting client ..." << std::endl;
	c.run();

	while(!c.isStopped()) {}
	return 0;
}





