#include <stdio.h>

#include "assembler.h"

void usage();
void test_assembler();

int main(int argc, char **argv)
{
    test_assembler();
    return (0);
}

void usage()
{
    printf("./emulator -i filename.asm\n");
}

void test_assembler()
{
    char *asm_file = "simple_add.asm";
    char *instructions_data = "instructions.txt";

    init_assembler(instructions_data, asm_file);

    assemble();
}