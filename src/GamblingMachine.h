/*
 * GamblingMachine.h
 *
 *  Created on: Oct 23, 2017
 *      Author: mrowacz
 */

#ifndef GAMBLINGMACHINE_H_
#define GAMBLINGMACHINE_H_

namespace game {

	class server {
		void worker();
	};

	class client {
	private:
		void worker();
	};
}

#endif /* GAMBLINGMACHINE_H_ */
