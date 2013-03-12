#include "catapult.h"
#include <iostream>
#include <string>
#include <sstream>

double m;
double r;

catapult::catapult(void)
{
}

catapult::~catapult(void)
{
}

void set_up_ball(double m, double r)
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
	return sqrt(m / (c * G)) * (atan(sqrt(c / (m*G)) * v0y) - acos(1 / (exp(c * h /m) * sqrt(1 + c / (m*G) * pow(v0y,2)))));
}

double flight_distance_ar(double v0, double theta, double h, double c, double t)
{
	double v0x = v0 * cos(theta);
	return m / c * log(1 + v0x * c * t / m);
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
    double i_bar = rod_mass*pow(len,2)/3;
    double i_proj = proj_mass*pow(len,2);
    return i_bar + i_proj;
}

/*
 * Calculate the length of the spring using law of cosines
 * height       Height of the support the spring is attached to
 * length       Length of the throwing arm, from aforementioned support to spring
 * angle        Angle between throwing arm and support
 */
double spring_length(double height, double length, double angle) {
    return sqrt(pow(height,2) + pow(length,2) - 2*height*length*cos(angle));
}

/*
 * Find the maximum release angle for a certain arm length
 */
double max_release(double length, double height) {
    return acos(height/length);
}

using namespace std;

int main(int argc, const char * argv[])
{
    double height = .20;
    double arm_len = 0.0;
    if(argc>1) {
        arm_len = atof(argv[1]);
    }
    if(arm_len==0.0){
        arm_len = .20*sqrt(2);
    }
    double k = 691.88;
    double stretch;
    double final;
    double v0;
	double theta = 45;
	double t;
	double x;
    double u = 20.669;
    
    theta = max_release(arm_len, height);
    cout << "Release angle: " << theta << endl;
    stretch = spring_length(height, arm_len, radians(80));
    final = spring_length(height, arm_len, theta);
    cout << stretch << endl;
    cout << final << endl;
    u = spring_potential(k, stretch)-spring_potential(k, final);
    cout << u << endl;
    cout << rotational_inertia(arm_len, 0, .1, .021) << endl;
    v0 = velocity(u, rotational_inertia(arm_len, 0, .1, .021))*arm_len;
    cout << v0 << endl;
	t = flight_time(v0, theta, height);
	x = flight_distance(v0, theta, t);
	cout << x << endl;
	return 0;
}
