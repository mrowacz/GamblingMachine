/*
 * GamblingMachine.h
 *
 *  Created on: Oct 23, 2017
 *      Author: mrowacz
 */

#ifndef GAMBLINGMACHINE_H_
#define GAMBLINGMACHINE_H_

#include <thread>
#include <iostream>
#include <boost/asio.hpp>

namespace game {

	constexpr unsigned int max_length = 256;
	constexpr unsigned int port = 9999;
	constexpr char serverTag[] = "[SERVER]:";

	class entity {
	protected:
		virtual void worker() = 0;
		std::thread th;
		bool finished;
	public:
		void run();
		bool isStopped();

		entity() : finished(false) {};
		virtual ~entity();
	};

	class server : public entity {
		void worker();
		void session(boost::asio::ip::tcp::socket sock);
	public:
		~server() {}
	};

	class client : public entity {
		void worker();
	public:
		~client() {}
	};
}

#endif /* GAMBLINGMACHINE_H_ */
