#include <stdio.h>
#include <stdlib.h>

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
    char *filename = "instructions.txt";

    load_instruction_table(filename);
    print_instruction_table();

    add_instruction("add", 'R', 0, 0);

    // Test getter functions. (addi)
    printf("addi: %c, %d, %d\n",
           get_instruction_type_by_name("addi"),
           get_instruction_funct_by_name("addi"),
           get_instruction_opcode_by_name("addi"));
}