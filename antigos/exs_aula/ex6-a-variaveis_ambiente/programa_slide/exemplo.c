#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    char next_option;
    while ((next_option = getopt(argc, argv, "a::b:")) != -1)
    {
        switch (next_option)
        {
        case 'a':
            printf("-a foi incluído, seu valor associado é: %s\n", optarg);
            break;
        case 'b':
            printf("-b foi incluído, seu valor associado é: %s\n", optarg);
            break;
        default:
            perror("%Argumentos: -a [Valor Op.] -b [Valor Ob.]\n");
            return 1;
        }
    }
    return 0;
}
