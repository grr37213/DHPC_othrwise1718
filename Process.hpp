
#include "mat.hpp"
#include "Latch.hpp"
#include <chrono>
#include <functional>
#include <thread>

using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
using Duration = std::chrono::duration<std::chrono::high_resolution_clock>;

class Process
{
	TimePoint start, finish;

	mat& m;
	std::function<double(double)> f;
	
	Latch& latch;

	std::thread t;

public:
	Process(mat& m, std::function<double(double)> f, Latch& l);

	virtual void body() = 0;

	void fire();
	void run();
	Duration complete();
	Duration runtime() const;
};
