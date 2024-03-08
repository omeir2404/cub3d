#include "parsing.h"


/**
 * @brief test main 
*/
int main(int argc, char **argv)
{
	t_map map;
	int ret;

	ret = 0;
	if(parser(argc, argv, &map) == -1)
		return -1;
	free_mapS(&map);
	return (ret);
}