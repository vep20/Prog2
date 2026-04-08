#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char **argv, char **envp){
    char next;

    while ((next = getopt(argc, argv, "a::n:")) != -1){

        switch (next){
        case 'a':
            /* code */
            break;
        
        case 'n'

            break;
        default:
            break;
        }
    }

    return 0;
}