#include <stdio.h>

#include "register.h"

void usage();
void test_register();

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
    test_register();
    return (0);
}

void usage()
{
    printf("./emulator -i filename.asm\n");
}

void test_register()
{
    // Initialize the register table
    init_register_table();

    // Print the register table
    print_register_table();

    // Set the register table
    set_register(0, 1);
    set_register(1, 2);
    set_register(2, 3);

    // Print the register table
    print_register_table();
}