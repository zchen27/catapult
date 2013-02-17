#include "catapult.h"
#include <math.h>
#include <stdio.h>
#include <iostream>


catapult::catapult(void)
{
}

catapult::~catapult(void)
{
}

double radians(double degrees)
{
	return degrees * PI / 180;
}

/*
*	Find time airborne
*/

double flight_time(double v0, double theta, double h)
{
	double b = v0 * sin(theta);
	double det = sqrt(pow(b, 2) + 2 * G * h);
	return (b + det) / G;
}

/*
*	Range, no air resistance
*/

double flight_distance(double v0, double theta, double t)
{
	return v0 * cos(theta) * t;
}

using namespace std;

int main()
{
	double v0;
	double theta;
	double h;
	double t;
	double x;

	theta = radians(theta);
	t = flight_time(v0, theta, h);
	x = flight_distance(v0, theta, t);
	cout << x << endl;
	return 0;
}
