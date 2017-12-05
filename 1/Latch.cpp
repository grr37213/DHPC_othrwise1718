#include "Latch.hpp"

#include <thread>
#include <exception>

Latch::Latch(unsigned int count):
count(count)
{}

void Latch::await(unsigned long stepms, unsigned long maxms)
{
	while(!check())
	{
		std::this_thread::sleep(stepms);
		maxms -= stepms;
		if(maxms < 0) throw std::exception("Thread not returning ! Latch wait time exceeded !");
	}
	
}

void Latch::countDown()
{
	count--;
}
