#include "catapult.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

double m = 0.2; //kg
double r = 0.0125; //m
//double c = 0.5 * RHO * CD * PI * pow(r, 2);
double c = VERY_SMALL_NUMBER;

double work_spring(double theta)
{
	double W;
	//W = fnInt(torque, theta, 0, theta)
	W = (11.2803 * pow(theta, 4)) - (16.751 * pow(theta, 3)) + (16.5485 * pow(theta, 2)) + (0.7801 * theta);
	return W;
}

double work_gravity(double theta)
{
	double W;
	W = -1 * ((sin(theta) * LENGTH_BAR / 2 * MASS_BAR * G) + (sin(theta) * (LENGTH_BAR - r) * G));
	return W;
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

double flight_time_ar(double v0, double theta, double h)
{
	double v0y = v0 * sin(theta);
	double temp1 = sqrt(m / (c * G));//
	double temp2 = sqrt(c / (m * G)) * v0y;
	double temp3 = atan(temp2);//
	double temp4 = c * h / m;
	double temp5 = 1 * pow(E, temp4);
	double temp6 = 1 + (c / (m * G) * pow(v0y, 2));
	double temp7 = 1 / (temp5 * sqrt(temp6));
	double temp8 = acos(temp7);//
	//double t = sqrt(m / (c * G)) * (atan(sqrt(c / (m*G)) * v0y) - acos(1 / (pow(E, (c * h /m)) * sqrt(1 + (c / (m*G) * pow(v0y,2))))));
	double t = temp1 * (temp3 - temp8);
	return t;
}

double flight_distance_ar(double v0, double theta, double t)
{
	double v0x = v0 * cos(theta);
	double x =  m / c * log(1 + v0x * c * t / m);
	return x;
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
    double i_bar = rod_mass*pow((len/2),2)/12 + rod_mass*pow(offset,2); //Not exactly on the edge
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
    /*double height = .20;
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
    cout <<"stretch: " << stretch << endl;
    cout <<"final: " << final << endl;
    //u = spring_potential(k, stretch)-spring_potential(k, final);
	u = work_spring(theta);
    cout <<"U: "<< u << endl;
    cout <<"I: "<< rotational_inertia(arm_len, 0, .1, .021) << endl;
    v0 = velocity(u, rotational_inertia(arm_len, 0, .1, .021))*arm_len;
    cout <<"v0: "<< v0 << endl;
	t = flight_time(v0, theta, height);
	x = flight_distance(v0, theta, t);
	cout <<"x: "<< x << endl;
	*/

	double thetad = 0;
	double thetar = radians(thetad);
	double U;
	double I;
	double omega;
	double v0;
	double t;
	double x;
	double alpha = radians(36.0);
	double bench = 0.6096;

	ofstream results;
	results.open("results.txt");
	results << "angel: \t";
	results << "x: "<< endl;
	while (thetad <= 60)
	{
		
		thetar = radians(thetad);
		U = work_spring(thetar) - work_gravity(thetar);
		I = rotational_inertia(LENGTH_BAR, (LENGTH_BAR /  2 - 0.02), m, (LENGTH_BAR));
		omega = velocity(U, I);
		v0 = omega * (0.25); //offset from edge
		t = flight_time(v0, alpha, (sin(alpha) * LENGTH_BAR + bench));
		x = flight_distance(v0, alpha, t);
		cout << "thetad: " << thetad << endl;
		results << thetad << "\t";
		cout << "thetar: " << thetar << endl;
		cout << "U: " << U << endl;
		cout << "I: " << I << endl;
		cout << "omega: " << omega << endl;
		cout << "v0: " << v0 << endl;
		cout << "t: " << t<< endl;
		cout << "x: " << x << endl;
		results << x << endl;
		cout << "" << endl;
		thetad++;
	}

	

	/*results.open("results.txt");
	results << "test"<< endl;
	results << "thetad: /t"<<;
		results << "thetar: /t" <<;
		results << "U: /t/t" <<;
		results << "I: /t/t" << I << endl;
		results << "omega: /t" << omega << endl;
		results << "v0: /t/t" << v0 << endl;
		results << "t: /t/t" << t<< endl;
		results << "x: /t/t" << x << endl;
		results << "" << endl;*/

	//insert while loop that cycles through all possible angles by increments of 1 degree.
	results.close();
	return 0;
}
