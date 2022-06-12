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
    const char *asm_file = "simple_add.asm";
    const char *instructions_data = "instructions.txt";

    init_assembler(instructions_data, asm_file);

    assemble();
}