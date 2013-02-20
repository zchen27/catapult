#pragma once

#include <math.h>

class catapult
{
public:
	catapult(void);
	~catapult(void);
	#define G 9.8
	#define CD 0.47
	#define RHO 1.293
	#define E 2.71828
	#define VERY_SMALL_NUMBER pow(1.0,-8.0)
	#define R 0.0 //Temp Value
	#define K 0.0 //Temp Value
	#define I 0.0 //Temp Value
	#ifndef M_PI
	#define PI atan(1.0)*4
	#else
	#define PI M_PI
	#endif
};

