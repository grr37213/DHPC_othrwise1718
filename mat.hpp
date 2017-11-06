
#include <iostream>
#include <functional>

class mat
{
	double * data;
	unsigned int m_rows, m_columns;
public:
	//m rows, n columns
	mat(unsigned int rows ,unsigned int columns);
	mat(const mat&);

	~mat();

	double get(unsigned int row, unsigned int column) const;
	void set (unsigned int row, unsigned int column, double& d);

	unsigned int getRows() const;
	unsigned int getColumns() const;
	
	void process(std::function<double(double)> f);
	void processLU(std::function<double(double)> f);
	void processRD(std::function<double(double)> f);

	void init_zero();
	void init_random(double fMin = -1000.0, double fMax = 1000.0);

	mat& operator= (const mat&);
	bool operator== (const mat& rhs) const;

	friend std::ostream& operator<< (std::ostream& os, const mat& m);
};
