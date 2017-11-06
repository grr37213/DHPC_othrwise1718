
#include "mat.hpp"
#include <chrono>

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
using Duration = std::chrono::duration<std::chrono::high_resolution_clock>;

class Process : public std::thread
{
	TimePoint start, finish;

	mat& m;
	std::function<double(double)> f;
public:
	Process(mat&, std::function<double(double>, Latch);

	void body() = 0;

	void start();
	Duration complete();
	Duration runtime();
};
