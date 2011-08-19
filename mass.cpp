//		(c) James Kristoff 2010
#include "mass.h"

//Initialize static and constant variables
int mass::cnt = 0;
double mass::dt = 1;
const double mass::PI = 3.1415926535897932384626433;
const double mass::Gn = 6.67428E-11;

//Default Ctor
mass::mass ()
{
	++cnt;
	pos[0] = 0;
	pos[1] = 0;
	vel[0] = 0;
	vel[1] = 0;
	acc[0] = 0;
	acc[1] = 0;
	force[0] = 0;
	force[1] = 0;
	radOrig = 1;
	radNow = radOrig;
	massKg = 100;
	area = getArea(radOrig);
	circ = getCirc(radOrig);
	squish = .5;
	isCollided = false;
}
//Overloaded Ctors
mass::mass (double x, double y, double rad, double xVel, double yVel, double xAcc, double yAcc, double aMass, double sqsh)
{
	++cnt;
	pos[0] = x;
	pos[1] = y;
	vel[0] = xVel;
	vel[1] = yVel;
	acc[0] = xAcc;
	acc[1] = yAcc;
	force[0] = 0;
	force[1] = 0;
	radOrig = rad;
	radNow = rad;
	massKg = aMass;
	area = getArea(radOrig);
	circ = getCirc(radOrig);
	squish = sqsh;
	isCollided = false;
}
mass::mass (double x, double y, double rad, double aMass, double sqsh)
{
	++cnt;
	pos[0] = x;
	pos[1] = y;
	vel[0] = 0;
	vel[1] = 0;
	acc[0] = 0;
	acc[1] = 0;
	force[0] = 0;
	force[1] = 0;
	radOrig = rad;
	radNow = rad;
	massKg = aMass;
	area = getArea(radOrig);
	circ = getCirc(radOrig);
	squish = sqsh;
	isCollided = false;
}
mass::mass (double x, double y)
{
	++cnt;
	pos[0] = x;
	pos[1] = y;
	vel[0] = 0;
	vel[1] = 0;
	acc[0] = 0;
	acc[1] = 0;
	force[0] = 0;
	force[1] = 0;
	radOrig = 1;
	radNow = radOrig;
	massKg = 100;
	area = getArea(radOrig);
	circ = getCirc(radOrig);
	squish = .5;
	isCollided = false;
}

//Copy ctor
mass::mass (const mass& M)
{
	for (int i = 0; i < 2; i++)
	{
		pos[i] = M.pos[i];
		vel[i] = M.vel[i];
		acc[i] = M.acc[i];
		force[i] = M.force[i];
	}
	radOrig = M.radOrig;
	radNow = M.radNow;
	massKg = M.massKg;
	area = M.area;
	circ = M.circ;
	squish = M.squish;
	isCollided = M.isCollided;
}
//Dtor
mass::~mass ()
{
	--cnt;
}
//Accessor Functions
double mass::getArea (double &rad)
{
	return PI*pow(rad,2);
}
double mass::getCirc (double &rad)
{
	return 2*PI*rad;
}
double mass::getRad ()
{
	return radNow;
}
double mass::getPosX ()
{
	return pos[0];
}
double mass::getPosY ()
{
	return pos[1];
}
//Modifier Functions
void mass::setDt(const double &Dt)
{
	dt = Dt;
}
void mass::setRad (const double &rad)
{
	radNow=rad;
}
void mass::setMass (const double &aMass)
{
	massKg=aMass;
}
void mass::setPos(const double &x, const double &y)
{
	pos[0] = x;
	pos[1] = y;
}
void mass::setVel(const double &x, const double &y)
{
	vel[0] = x;
	vel[1] = y;
}
void mass::setAcc(const double &x, const double &y)
{
	acc[0] = x;
	acc[1] = y;
}

//Helper Functions
void mass::getForce (mass &blob)
{
	double totForce = 0, theta=0;
	double dist = 0, xDist=0, yDist=0;
	xDist = (blob.pos[0] - pos[0]);
	yDist = (blob.pos[1] - pos[1]);
	dist = sqrt( pow(xDist,2.0) + pow(yDist,2.0));
	theta = atan2(yDist, xDist);//in Radians
	if(dist <= (getRad() + blob.getRad()))//if the masses have collided...
	{
		isCollided=true;
		blob.isCollided=true;
	}
	else
	{
		totForce = Gn * ((massKg * blob.massKg)/pow(dist,2.0));
		force[0] += cos(theta) * totForce;
		force[1] += sin(theta) * totForce;
		blob.force[0] += cos(theta) * totForce * -1.0;
		blob.force[1] += sin(theta) * totForce * -1.0;
	}
}
//Calculate Forces between All Masses
void mass::calcForces(mass aryMass[])
{
	for (int k = 0; k < cnt; k++)
	{
		aryMass[k].force[0] = 0;
		aryMass[k].force[1] = 0;
	}
	for (int i = 0; i < cnt; i++)
	{
		for (int j = cnt-1; j - i >= 1; j--)
		{
			aryMass[i].getForce(aryMass[j]);
		}
		aryMass[i].calcAcc();
		aryMass[i].calcVel(dt);
		aryMass[i].calcPos(dt);
	}
}
//Calculates the Acceleration
void mass::calcAcc()
{
	if(!isCollided)
	{
		acc[0] = force[0] / massKg;
		acc[1] = force[1] / massKg;
	}
}
//Calculates the velocity after some dt
void mass::calcVel(double &dt)
{
	if(!isCollided)
	{
		vel[0] += acc[0] * dt;
		vel[1] += acc[1] * dt;
	}
}
//Calculates the position after some dt
void mass::calcPos(double &dt)
{
	if(!isCollided)
	{
		pos[0]+=vel[0] * dt+(0.5) * acc[0] * pow(dt,2.0);
		pos[1]+=vel[1] * dt+(0.5) * acc[1] * pow(dt,2.0);
		//keepOnScreen();
	}
}
void mass::keepOnScreen()
{
	// keeps object on the screen in the x direction.
	if(pos[0] >= 620 + radNow || pos[0] <= -620 - radNow)
	{
		pos[0] = -1 * sign(pos[0]) * 620 - 1 * sign(pos[0]) * radNow;
	}
	// keeps object on the screen in the y direction.
	if(pos[1] >= 425 + radNow || pos[1] <= -425 - radNow)
	{
		pos[1] = -1 * sign(pos[1]) * 425 -1 * sign(pos[1]) * radNow;
	}
}
// Overload << operator for mass
std::ostream& operator<< (std::ostream &os,  const mass &aMass)
{
	os << aMass.pos[0] << ","	<< aMass.pos[1] << "," << aMass.radNow;
	return os;
}