#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COUNT 3762


extern int lookup[100][2];

#define PI 3.141592653589793

int main(int argc, char *argv[]) {

	double look;
	double stepsize;
	double currentstep;
	int stepcount=0;
	int level=0;
	int temp=0;
	stepsize = (2.00 * PI) / 100.00;

	for (currentstep = stepsize / 2.00; currentstep < 2.00 * PI; currentstep +=stepsize)
	{
		level=1;
		look = 4.00*COUNT*sin(currentstep);
		if(look<0)	look*=-1.00;
		while(round(look)>COUNT)
		{
			level++;
			look-=COUNT;
		}
		printf("%d %d, %f, %d, %d, %f\n",++stepcount, level, currentstep*180.00/PI, (int)round(look),(int)(COUNT-round(look)), look);
    }
	for (currentstep = stepsize / 2.00; currentstep < 2.00 * PI; currentstep +=stepsize)
		{
			level=1;
			look = 4.00*COUNT*sin(currentstep);
			if(look<0)	look*=-1.00;
			while(round(look)>COUNT)
			{
				level++;
				look-=COUNT;
			}
			if(temp!=level) printf("\n");
			printf("{%d,%d},  ", (int)round(look), (int)(COUNT-round(look)));
			temp=level;
	    }
	stepcount=0;
	for (currentstep = stepsize / 2.00; currentstep < 2.00 * PI; currentstep +=stepsize)
			{
				look = 4.00*COUNT*sin(currentstep);
				if(look<0)	look*=-1.00;
				while(round(look)>COUNT)
				look-=COUNT;
				printf("\n%d\t",stepcount+1);
				if((int)round(look)!=lookup[stepcount][0]||(int)(COUNT-round(look))!=lookup[stepcount++][1])
					printf("Matrix Entry mismatch!");
				else printf("Matrix Entry confirmed.");
			}
	return 0;
}
