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

double flight_time_ar(double v0, double theta, double h, double c)
{
	double v0y = v0 * sin(theta);
	return 0;
}

double flight_distance_ar(double v0, double theta, double h, double c)
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

/*
 * Calculate rotational inertia
 * len          Total length of throwing arm
 * offset       Distance from pivot to center of mass (positive = right)
 * rod_mass     Mass of throwing arm
 * proj_mass    Mass of projectile
 */
double rotational_inertia(double len, double offset, double rod_mass, double proj_mass)
{
    double i_bar = rod_mass*pow(len,2)/2 + rod_mass*pow(offset,2)/2;
    double i_proj = proj_mass*pow(len/2+offset,2)/2;
    return i_bar + i_proj;
}

using namespace std;

int main()
{
	double v0;
	double theta;
	double h;
	double t;
	double x;
    double u;
    
    v0 = velocity(u, rotational_inertia(5, 0, 1, 1));
	theta = radians(theta);
	t = flight_time(v0, theta, h);
	x = flight_distance(v0, theta, t);
	cout << x << endl;
	return 0;
}
