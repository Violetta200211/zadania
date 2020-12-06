/*
 * globals.h
 *
 *  Created on: 28 окт. 2019 г.
 *      Author: prepod
 */

#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <SDL2/SDL.h>
#include <stdexcept>
#include <string>
#include <cmath>

static constexpr double
	Pi = acos(-1);
static inline void SDL_DIE(const char * where)
{
	throw std::runtime_error(
			std::string(where) +
			std::string(": ") +
			std::string(SDL_GetError()));
}



#endif /* GLOBALS_H_ */
