
#include "Process.hpp"
#include <thread>

Process::Process(mat& m, std::function<double(double)> f, Latch& l)
l(l),
m(m),
f(f),
running(false),
std::thread(start)
{
}

void Process::start()
{
	start = std::chrono::high_resolution_clock::now();
	body();
	latch.countDown();
}

void complete()
{
	latch.await();
	finish = std::chrono::high_resolution_clock::now() - start;
	return finish;
}

Duration runtime () const
{
	return finish;
}


