#include "parsing.h"

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
    while (file[len - 4 + i] && ext[i] )
    {
        if (file[len - 4 + i] != ext[i])
            return (-1);
        i++;
    }
    return (0);
}

int check_file_access(char *file)
{
    if (!(access(file, R_OK) == 0))
        return (-1);
    return (0);
}

int check_args(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("./cub3d file_path: number of args given: %d \n", -2);
        return (-1);
    }
    if (check_file_extension(argv[1]) == -1)
    {
        printf("file must end with .ber");
        return (-2);
    }
    if (check_file_access(argv[1]) == -1)
    {
        printf("%d \n", -3);
        return (-3);
    }
    return (0);
}