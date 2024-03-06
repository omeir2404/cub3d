#include "parsing.h"


t_control *get_game_control(){
    static t_control control;

    return(&control); 
}

/**
 * @brief checks if the file given has the correct extension to be readable
 * @return 0 if correct, -1 if not correct
*/
int check_file_extension(char *file)
{
    int i;
    int len;
    char *ext;

    len = strlen(file);
    ext = ".cub";

    i = 0;
    while (file[len - 1] == ' ')
        len--;
    while (file[len - 4 + i] && ext[i])
    {
        if (file[len - 4 + i] != ext[i])
            return (-1);
        i++;
    }
    return (0);
}

/**
 * @brief checks if the file exists and given has the correct permissions to be readable
 * @return 0 if correct, -1 if not correct
*/
int check_file_access(char *file)
{
    char *give;
    int start;
    int end;
    int i;

    i = 0;
    start = 0;
    while (file[start] == ' ')
        start++;
    end = (int)ft_strlen(file) - 1;
    while(file[end] == ' ')
        end--;
    give = (char *)malloc((end - start) + 2);
    while(start <= end)
        give[i++] = file[start++];
    give[i] = '\0';
    if (!(access(give, R_OK) == 0))
    {
        free(give);
        return (-1);
    }
    free(give);
    return (0);
}

/**
 * @brief checks if arguments follow the given rules
 * @return 0 if args are correct, >0 if incorrect
*/
int check_args(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("./cub3d file_path: number of args given: %d\nargs needed: 2\n", argc);
        return (-1);
    }
    if (check_file_extension(argv[1]) == -1)
    {
        printf("file must end with .ber");
        return (-2);
    }
    if (check_file_access(argv[1]) == -1)
    {
        printf("NO ACCESS sus \n");
        return (-3);
    }
    return (0);
}
