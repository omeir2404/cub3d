#include "parsing.h"

int check_file_extension(char *file)
{
    int i;
    int len;
    char *ext;

    len = ft_strlen(file);
    i = len - 1;
    ext = ".cub";
    printf("--------%s-------\n", file);
    // while (file[len - 1] == ' ')
    //     len--;
    while (i < len)
    {
        printf("------file[i]: %c -----\n------ext[len-i]: %c -----\n ---i: %d---\n", file[i],ext[len-i], i);
        if (file[i] != ext[len - 4 + i
        ])
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
        printf("%d \n", -1);
        return (-1);
    }
    if (check_file_extension(argv[1]) == -1)
    {
        printf("%d \n", -2);
        return (-2);
    }
    if (check_file_access(argv[1]) == -1)
    {
        printf("%d \n", -3);
        return (-3);
    }
    return (0);
    
}