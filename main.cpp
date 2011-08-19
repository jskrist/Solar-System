#include <cmath>
#include <fstream>
#include <time.h>
#include "mass.h"

int main()
{
	mass::setDt(0.1);
	static time_t seconds;
	time_t relSeconds;
	std::ofstream file;
	file.open ("./grav.csv");

	//double dt = 1;//10.0 / 6.0;//seconds
	const int numMass = 3;
	mass aMass[numMass];


	aMass[0] = new mass(0,0,25,0,0,0,0,1.0E14,0);
	aMass[1] = new mass(-250,0,10,0,5,0,0,5.2E12,0);
	aMass[2] = new mass(-300,0,4,0,1,0,0,5.2E10,0);		//cool Orbit
//	aMass[2] = mass(-300,0,4,0,2.5,0,0,5.2E10,0);	//Orbiting moon

	////Solar System
	//aMass[0] = mass(0,0,6.955E8,0,0,0,0,1.98892E30,0);//Sun
	//aMass[1] = mass(5.790905E10,0,2.4397E6,0,-47870,0,0,3.3022E23,0);//Mercury
	//aMass[2] = mass(1.08209184E11,0,6.0518E6,0,-35020,0,0,4.8685E24,0);//Venus
	//aMass[3] = mass(1.495978707E11,0,6.3781E6,0,-29780,0,0,5.9742E24,0);//Earth
	////aMass[4] = new mass(1.499803707E11,0,1.7374E6,0,30780,0,0,7.36E22,0);//Moon
	//aMass[4] = mass(2.2793915E11,0,3.3962E6,0,-24077,0,0,6.4185E23,0);//Mars
	//aMass[5] = mass(7.785472E11,0,7.1492E7,0,-13070,0,0,1.8986E27,0);//Jupiter
	//aMass[6] = mass(1.43344937E12,0,6.0268E7,0,-9690,0,0,5.6846E26,0);//Saturn
	//aMass[7] = mass(2.876679083E12,0,2.5559E7,0,-6810,0,0,8.681E25,0);//Uranus
	//aMass[8] = mass(4.503443662E12,0,2.4764E7,0,-5430,0,0,1.0243E26,0);//Neptune
	//aMass[9] = mass(0,5.906376272E12,1.153E6,4666,0,0,0,1.305E22,0);//Pluto

	seconds = time (NULL);
	relSeconds = seconds;
	for (int i = 0; i < numMass; i++)
	{
		if (i < numMass - 1)
		{
			file << aMass[i] << ",";
		}
		else
		{
			relSeconds = time (NULL);
			relSeconds -= seconds;
			file << aMass[i] << "," << relSeconds << "\n";
		}
	}
	for(int i=0; i<4000000;i++)//about one neptunian year
	{
		mass::calcForces(aMass);
		for (int j=0;j<numMass;j++)
		{
			if(i%20000==0)
			{
				if (j<numMass-1)
				{
					file << aMass[j] << ",";
				}
				else
				{
					relSeconds = time (NULL);
					relSeconds -= seconds;
					file << aMass[j] << "," << relSeconds << "\n";
				}
			}
		}
	}
	file.close();
	return 0;
}
