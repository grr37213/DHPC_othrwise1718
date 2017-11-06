
#include <boost/numeric/mtl/mtl.hpp>
#include <functional>

class mat2 : public mtl::dense2D<double>
{
public:
	mat2(unsigned int x , unsigned int y);
	~mat2();

	void init_random();
	void init_zero();

	void process(std::function<double(double)>);
	void processLU(std::function<double(double)>);
	void processRD(std::function<double(double)>);	
};
