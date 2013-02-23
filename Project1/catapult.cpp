#include "catapult.h"
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

/*
*	Now with air resistance (unfinished)
*/

double flight_time(double v0, double theta, double h, double c)
{
	double v0y = v0 * sin(theta);
	return 0;
}

double flight_distance(double v0, double theta, double h, double c)
{
	double v0x = v0 * cos(theta);
	return 0;
}


/*
 * Potential energy of a spring
 * Remove parameter k when design is complete
 */
double spring_potential(double k, double x)
{
    return k/2 * pow(x, 2);
}

/*
 * Find velocity from kinetic energy
 */
/*double velocity(double m, double kinetic)
{
    return sqrt(2*kinetic/m);
}*/

/*
*	Slightly easier way of finding velocity with Ke=I * omega ^ 2
*	Remove parameter I when design is complete
*/
double velocity(double usp, double i)
{
	return sqrt(2*usp/i);
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
