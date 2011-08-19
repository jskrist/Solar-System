/*	

	(c) James Kristoff 2010

	A class to initially represent circular squishable mass
	which should eventually be extended to spherical mass.

	Mass will have a radOrig which will be the original 
	radius, radNow which is the current radius, massKg which 
	will represent the amount of mass in kg, and squish with
	values from 0 to 1 is a percent that the mass can be
	squished or stretched.
*/

#ifndef JAMES_K_MASS_H
#define JAMES_K_MASS_H
#include <iostream>
#include <cmath>

class mass {
	private:
		//original and current radius, mass and squish quotient
		double radOrig, radNow, massKg, squish;
		double area, circ;	//area and circumference of the mass
		double pos[2], vel[2], acc[2], force[2];	//x and y velocity
		static double dt;
		const static double PI, Gn;
		static int cnt;	//number of masses
		bool isCollided;

		//Member Functions
        template <class T>
        T sign(T num)
		{
			if(num < 0)
				return -1;
			else
				return 1;
		}
		void getForce (mass&);
		void keepOnScreen();
		//Calculates the Acceleration
		void calcAcc();
		//Calculates the velocity after some dt
		void calcVel(double &dt);
		//Calculates the position after some dt
		void calcPos(double &dt);
	public:
		//Member Functions
		friend std::ostream& operator<< (std::ostream&, const mass&);
		//Calculate Forces between All Masses
		static void calcForces(mass[]);

		//Accessor Functions
		double getArea (double&);
		double getCirc (double&);
		double getRad ();
		double getPosX ();
		double getPosY ();

		//Modifier Functions
	    void setRad (const double&);
	    void setMass (const double&);
		void setPos(const double&, const double&);
		void setVel(const double&, const double&);
		void setAcc(const double&, const double&);
		static void setDt(const double&);

		//	Constructors
		mass (double x, double y, double rad, double xVel, double yVel, double xAcc, double yAcc, double aMass, double sqsh);
		mass (double x, double y, double rad, double aMass, double sqsh);
	    mass (double x, double y);
	    mass ();
		mass(const mass&);
		//Destructor
		~mass ();
};
#endif