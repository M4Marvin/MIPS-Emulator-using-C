#include <stdio.h>

#include "instruction.h"

void usage();
void test_instruction();

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
    test_instruction();
    return (0);
}

void usage()
{
    printf("./emulator -i filename.asm\n");
}

void test_instruction()
{
    printf("test_instruction\n");

    char *filename = "data/instructions.txt";

    load_instruction_table(filename);
    print_instruction_table();
}