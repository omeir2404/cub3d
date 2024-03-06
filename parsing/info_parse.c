#include "parsing.h"

/**
 * @brief aux function for {@code parse_colors}
 * 
 * @param mat 
 * @param name 
 * @return 0 if okay, -1 if not okay
 */
int check_color_num(char **mat, char *name)
{
    int i;
    int num;

    i = 0;
    num = 0;
    while (mat[i])
    {
        num = ft_atoi(mat[i]); 
        if (!(num >= 0 && num <= 255))
        {
            printf("number out of range for %s color\n", name);
            return (-1);
        }
        i++;
    }
    return (0);
}
/**
 * @brief checks if the colors of the floor and ceiling recieved are in range
 * 
 * @param map 
 * @return 0 if all okay, -1 if not
 */
int parse_colors(t_map *map)
{
    char **F;
    char **C;
    int ret;

    ret = 0;
    F = ft_split(map->floor, ',');
    C = ft_split(map->ceiling, ',');
    if (check_color_num(F, "floor") == -1)
        ret = -1;
    if (check_color_num(C, "ceiling") == -1)
        ret = -1;
    free_mat(F);
    free_mat(C);
    return (ret);
}

/**
 * @brief parses info recieved from map file (colors and paths)
 * 
 * @param map 
 * @return 0 if all okay, -1 if not
 */
int info_parse(t_map *map)
{
    if (parse_colors(map) == -1)
        return (-1);
    return (0);
}
