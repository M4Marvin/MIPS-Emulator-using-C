#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#include "emulator.h"

void usage();

int main(int argc, char **argv)
{
    // char *filename = "simple_add.asm", opt;
    // while ((opt = getopt(argc, argv, "i:h")) != -1)
    // {
    //     switch (opt)
    //     {
    //     case 'i':
    //         filename = malloc(strlen(optarg) + 1);
    //         strcpy(filename, optarg);
    //         break;
    //     case 'h':
    //         usage();
    //         return 0;
    //     case ':':
    //         printf("option needs a value\n");
    //         return 1;
    //     case '?':
    //         printf("unknown option: %c\n", optopt);
    //         break;
    //     }
    // }

    return (0);
}

void usage()
{
    printf("./emulator -i filename.asm\n");
    return;
}
