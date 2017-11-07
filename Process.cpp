
#include "Process.hpp"
#include <thread>

Process::Process(mat& m, std::function<double(double)> f, Latch& l)
	:
latch(l),
m(m),
f(f)
{
}


void Process::run()
{
	start = std::chrono::high_resolution_clock::now();
	body();
	latch.countDown();
}

void Process::fire()
{
	t = std::thread(&Process::run, this);
}

Duration Process::complete()
{
	latch.await();
	finish = std::chrono::high_resolution_clock::now();
	return runtime();
}

Duration Process::runtime() const
{
	return finish-start;
}
