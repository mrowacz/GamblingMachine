/*
 * main.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: mrowacz
 */

#include <string>
#include <chrono>
#include <thread>
#include <limits.h>
#include <unistd.h>
#include <iostream>
#include <boost/filesystem/path.hpp>

#include "GamblingMachine.h"

using namespace std;
namespace fs = boost::filesystem;

std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

int main(int argc, char *argv[])
{
	game::client c;

	std::string exePath = getexepath();
	std::string path(exePath.substr(0, exePath.length() - std::string("client").length()) + "server &");

	std::system(path.c_str());
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::cout << "Starting client ..." << std::endl;
	c.run();

	while(!c.isStopped()) {}
	return 0;
}





