
#include <stdio.h>
#include <stdlib.h>

#define diff(a,b) b-a

void swap_f(float * a, float * b)
{
	float tmp = *a;
	*a = *b;
	*b = tmp;
}

float rnd_f(float min, float max)
{
	if(min > max)
	{
		swap_f(&min, &max);
	}
	return (float)rand()/(float)(RAND_MAX/diff(min,max));
}

struct body
{
	float x, y, vx, vy, m;
};

body randombody	(	
					body min, body max
				)
{
	body b =	{
					rnd_f(min.x, max.x),
					rnd_f(min.y, max.y),
					rnd_f(min.vx, max.vx),
					rnd_f(min.vy, max.vy),
					rnd_f(min.m, max.m)
				};
	return b;
}

__global__ gravitate(body* bef, body *aft, int bodycount, float * stepsize)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if(bodycount < (idx + 1)) return 0;

	//clear the velocity value in aft to 0
	aft[idx].vx = 0.0;
	aft[idx].vy = 0.0;

	for(int i = 0; i < blockDim.x .x; i++)
	{
		float dx = bef[i].x - bef[idx].x;
		float dy = bef[i].y - bef[idx].y;

		float sqlen = dx * dx + dy + dy;
		float acceleration = bef[idx].m / sqlen;
		//normalize
		sqlen = sqrt(sqlen);
		dx = dx/sqlen;
		dy = dx/sqlen;

		//store in new value
		//not use += operator because of multiply-add compiler optimization
		//TODO test if it means anything

		aft[idx].vx = acceleration * dx + aft[idx].vx;
		aft[idx].vy = acceleration * dy + aft[idx].vy;

		//actual new velocity here then :
		aft[idx].vx += bef[idx].vx;

		//step
		aft[idx].x = aft[idx].vx * *stepsize;
		aft[idx].y = aft[idx].vy * *stepsize;
	}
}

#define LOOP_SAFETY 10000000

int run (unsigned int bodycount, float stepsize, float simtime, unsigned int blocksize, body * hostdata)
{
	unsigned int blockamount = bodycount / blocksize +1;

	int safetycounter = LOOP_SAFETY;

	body *d_1; body *d_2;

	cudaMalloc(d_1, sizeof(body) * bodycount);
	cudaMalloc(d_2, sizeof(body) * bodycount);

	//initialize the masses with 0
	//this is important since when there would be an uneven/suboptimal values of bodies threads would start in vain and calculate the force of their body
	//with no mass this calculation will not influence the result

	for(int i = 0; i < bodycount ; i++)
	{
		d_1[i].m = 0.0;
		d_2[i].m = 0.0;
	}

	cudaMemcpy(d_1, hostdata, bodycount*sizeof(body), cudaMemcpyHostToDevice);

	unsigned int blockamount = bodycount / blocksize;
	if(bodycount%blocksize) blockamount++;

	while (simtime > 0 && safetycounter > 0)
	{
		gravitate <<<  >>>	


		safetycounter--;
	}

	free(h_1);
}

#define DEFAULT_SIMTIME 10.0
#define DEFAULT_STEPSIZE 1.0
#define DEFAULT_BODYCOUNT 1024
#define DEFAULT_BLOCKSIZE 16

void help()
{
	printf("\n Help for nbody : \n\t nbody [Number of bodys] -[flag] [[flagvalue]]* \n\n Arguments : \n");
	printf("\t none\t Number of bodys to calculate as base 10 integer (Default : %d)\n", DEFAULT_BODYCOUNT);
	printf("\t-h\t Show this help\n");
	printf("\t-s\t Stepsize of simulation. Simulation will have simtime /stepsize round trips of duration given by step and one additional trip of simtime mod stepsize (Default : %f)\n", DEFAULT_STEPSIZE);
	printf("\t-t\t Time to simulate as a Float(Default : %f)\n", DEFAULT_SIMTIME);
	printf("\t-b\t Size of a Block / amount of threads on one Block (Default : %d\n)", DEFAULT_BLOCKSIZE);
	printf("\t-m[in/ax]\t A minimal/maximal set of values for random generated bodies. Write 5 floats for x/y position , x/y velocity and mass.\nExample\n\t\t -min [minx] [miny] [minvx] [minvy] [minm]\n")
	fflush(stdout);
}


int main (int argc, char ** argv)
{
	if(argc < 1)
	{
		printf("Wrong number of arguments !\nTry \n\n\t $ nbody -h\n\nfor help !");
	}

	int argi;

	//default initializations
	unsigned int bodycount = DEFAULT_BODYCOUNT;
	float stepsize = DEFAULT_STEPSIZE;
	float simtime = DEFAULT_SIMTIME;

	unsigned int blocksize = DEFAULT_BLOCKSIZE;

	body bmin = {-10000.0, -10000.0, -100.0, -100.0, 0};
	body bmax = {10000.0, 10000.0, 100.0, 100.0, 1000};

	//argument handling 
	for(argi = 0; argi < argc; argi++)
	{
		if(argv[argi][0] == '-')
		{
			switch(argv[argi][1])
			{
				case 'h':
					help(); exit(1);
				break;
				case 't':
					simtime = atof(argv[++argi]);
				break;
				case 's':
					stepsize = atof(argv[++argi]);
				break;
				case 'b':
					blocksize = atoi(argv[++argi]);
				break;
				case 'm':
					{
						body * bchange = (argv[argi][2] == 'i')? &bmin : &bmax;
						*bchange = {atof(++argi), atof(++argi),atof(++argi),atof(++argi),atof(++argi)};
				}
				break;
			}
		}
		else
		{
			bodycount = atoi(argv[argi]);
		}
	}

	//seed random number generator
	time_t t;
	srand((unsigned) time(&t));
	//in the following a random number can be generated

	//init data
	//allocate host mem
	body* h_1 = (body*)malloc(bodycount);

	//initialize random
	{
		for (body* ptr = h_1 ; ptr < h_1+bodycount; ptr++)
		{
			*ptr = randombody(bmin, bmax);
		}
	}

	return run(bodycount, stepsize, simtime, blocksize, h_1);
}

