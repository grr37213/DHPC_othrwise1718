
#include "mat.hpp"

#include <iostream>
#include <string.h>
#include <random>
#include <iomanip>

mat::mat(unsigned int rows, unsigned int columns)
	:
	m_rows(rows),
	m_columns(columns)
{
	data = new double [rows*columns];
}

mat::mat(const mat& rhs):
m_rows(rhs.m_rows),
m_columns(rhs.m_columns)
{
	data = new double [rhs.m_rows*rhs.m_columns];
	memcpy(rhs.data, data, rhs.m_rows*rhs.m_columns*sizeof(double));
}

mat::~mat()
{
	delete[] data;
}

double mat::get(unsigned int row, unsigned int column) const
{
	return data[m_columns*row + column];
}

void mat::set(unsigned int row, unsigned int column, double& d) 
{
	data [m_columns*row + column] = d;
}

unsigned int mat::getRows() const
{
	return m_rows;
}

unsigned int mat::getColumns() const
{
	return m_columns;
}

void mat::process (std::function<double(double)> f)
{
	for(unsigned int i = 0; i < m_rows*m_columns ; i++)
	{
		data[i] = f(data[i]);
	}
}

void mat::processLU (std::function<double(double)> f)
{
	if(m_rows == 0) return;
	if(m_rows != m_columns) return;
	for(unsigned int m = 0; m < m_rows; m++)
	{
		for(unsigned int n = 0; n < m_columns-m; n++)
		{
			data[m*m_columns+n] = f(data[m*m_columns+n]);
		}
	}
}

void mat::processRD (std::function<double(double)> f)
{
	if(m_rows == 0) return;
	if(m_rows != m_columns) return;
	for(unsigned int m = 1; m < m_rows; m++)
	{
		for(unsigned int n = m_columns - m ; n < m_columns; n++)
		{
			data[m*m_columns+n] = f(data[m*m_columns+n]);
		}
	}
}
void mat::init_zero()
{
	memset(data, 0, m_rows*m_columns*sizeof(double));
}

void mat::init_random(double fMin, double fMax)
{
    double f;
	for (unsigned int i = 0; i < m_rows*m_columns ; i++)
	{ 
		//generate random double value
		f = (double)rand() / RAND_MAX;
		data[i] = fMin + f * (fMax - fMin);
	}	
}

mat& mat::operator= (const mat& rhs)
{
	m_rows = rhs.m_rows;
	m_columns = rhs.m_rows;
	if(data) delete[] data;
	data = new double [m_rows*m_columns];
	memcpy(rhs.data, data, m_rows*m_columns*sizeof(double));
	return *this;
}

bool mat::operator== (const mat& rhs) const
{
	if(	m_rows != rhs.m_rows ||
		m_columns != rhs.m_columns	
	) return false;
	//any other value than 0 with memcmp means non-equal
	if(memcmp(data, rhs.data, m_rows*m_columns*sizeof(double))) return false;
	return true;
}

std::ostream& operator<< (std::ostream& os , const mat& ma)
{
	os << "Fixed precision output on 5 digits !\n" << std::setprecision(5);
	for(unsigned int m = 0; m < ma.m_rows; m++)
	{
		for(unsigned int n = 0 ; n < ma.m_columns; n++)
		{
			os << ma.data[m*ma.m_columns+n] << '\t';
		}
		os << '\n';
	}
	return os;
}
