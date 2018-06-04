#include <math.h>
#include <stdio.h>

int			main(void)
{
	float	i;
	i = 0;
	while (i < 1.1)
	{

	printf("log10 : %f ret :%f\n", i, log10(i));
		i += 0.1;
	}
	i = 0;
	while (i < 9)
	{

		printf("exp10 : %f ret :%f\n", i, __exp10(i));
		i += 1;
	}
	
	
	
	return (0);
}
