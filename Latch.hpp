
class Latch
{
	unsigned int count;
public:
	Latch(unsigned int count);
	void await(unsigned long stepms = 300, unsigned long maxms = 1000000);
	void countDown();
};
