#include <random>

#include "mat.hpp"
#include <cmath>

#include <iostream>

#include <cstdlib>


using std::cout;

int main (int argc , char** argv)
{
	//initialize random utility with a custom seed
	srand(42);

	int amount = 10;

	bool verbose = false;

	if(argc > 1)
	{
		amount = atoi(argv[1]);
	}

	if(argc > 2)
	{
		if(argv[2][0] == '-')
		{
			switch(argv[2][1])
			{
				case'v':
					verbose = true;
			}	
		}
	}

	mat m(amount,amount);
	m.init_random(-1.0,1000.0);

	if(verbose) cout << m << '\n';

	m.processLU(
				[]
				(double d)
				{
					return 1.0; 
				}
			);

	
	if(verbose) cout << m << '\n';

	return 0;
}
