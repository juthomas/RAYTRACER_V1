#include "includes/rt.h"

typedef struct		s_bo
{
	int wfwq;
	t_list	*list;



}					t_bo;



int main(int argc, char **argv)
{
	t_bo *bo;
	
	bo = (t_bo*)malloc(sizeof(*bo));


	bo->list = rt_parser_main(argc, argv);

	while (1)
		;

	return (0);
}
