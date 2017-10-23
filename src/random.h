/*
 * random
 *
 *  Created on: Oct 23, 2017
 *      Author: mrowacz
 */

#ifndef RANDOM_H_
#define RANDOM_H_

#include <iostream>
#include <random>
#include <iterator>

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
	std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
	std::advance(start, dis(g));
	return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	return select_randomly(start, end, gen);
}

#endif /* RANDOM_H_ */
