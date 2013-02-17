#pragma once

#include <math.h>;

class catapult
{
public:
	catapult(void);
	~catapult(void);
	#define G 9.8
	#ifndef M_PI
	#define PI atan(1.0)*4
	#else
	#define PI M_PI
	#endif
};

