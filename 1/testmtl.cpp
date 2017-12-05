
#include <iostream>
#include "mat2.hpp"

using namespace std;
using namespace mtl;

int main()
{

	dense2D<double> A(2, 2);
	cout << num_rows(A);

}
