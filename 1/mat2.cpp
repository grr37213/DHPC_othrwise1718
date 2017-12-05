
#include <random>
#include "mat2.hpp"

using namespace mtl;

mat2::mat2(unsigned int m, unsigned int n)
: dense2D<double>(m, n){}

void mat2::init_random()
{}
void mat2::init_zero()
{}

void mat2::process(std::function<double(double)> f)
{
	for(unsigned int m = 0; m < mtl::num_rows(*this); m++)
	{
		for(unsigned int n = 0; n < mtl::num_cols(*this); n++)
		{
			*this(m, n) = f(*this(m, n));
		}
	}
}

void mat2::processLU (std::function<double(double)> f)
{
	if(mtl::num_rows == 0) return;
	if(mtl::num_rows != mtl::num_cols(*this)) return;
	for(unsigned int m = 0; m < mtl::num_rows(*this); m++)
	{
		for(unsigned int n = 0; n < mtl::num_cols(*this)-m; n++)
		{
			*this(m, n) = f(*this(m, n));
		}
	}
}

void mat2::processRD (std::function<double(double)> f)
{
	if(mtl::num_rows(*this) == 0) return;
	if(numm_rows(*this) != mtl::num_cols(*this)) return;
	for(unsigned int m = 1; m < mtl::num_rows(*this); m++)
	{
		for(unsigned int n = mtl::num_cols - m ; n < numm_cols; n++)

		{
			*this(m, n) = f(*this(m, n));
		}
	}
}
void mat2::init_zero()
{
	process([](double d){return 0.0;});
}

void mat2::init_random(double fMin, double fMax)
{
	process([](double d){
	//generate random double value
	f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
	})
}	
