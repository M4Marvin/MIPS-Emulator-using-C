/**
 * Implementation of the instruction module.
 * This module is responsible for storing the opcodes of instructions.
 * It is also responsible for providing the opcode of the instruction.
 */
#include "instruction.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

// Define the struct Instruction containing data common to all instructions.
typedef struct Instruction
{
    const char *name;
    char type; // {'r', 'i', 'j'}
    uint8_t funct;
    uint8_t opcode;
} Instruction;

// Define the struct InstructionTable.
typedef struct InstructionTable
{
    Instruction *instructions;
    int size;
} InstructionTable;

InstructionTable instruction_table = {NULL, 0};

void load_instruction_table(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open instruction file.\n");
        exit(1);
    }

    // Read the number of instructions.
    int num_instructions;
    fscanf(file, "%d", &num_instructions);

    // Allocate memory for the instructions.
    instruction_table.instructions = malloc(num_instructions * sizeof(Instruction));
    if (instruction_table.instructions == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for instructions.\n");
        exit(1);
    }

    // Read the instructions.
    // The format of the file is:
    // <name> <description> <type> <funct> <opcode>
    for (int i = 0; i < num_instructions; i++)
    {
        char name[256];
        char type;
        uint8_t funct;
        uint8_t opcode;
        // Reading values from a line.
        fscanf(file, "%s %c %hhu %hhu", name, &type, &opcode, &funct);
    }

    // Close the file.
    fclose(file);

    // Set the size of the instruction table.
    instruction_table.size = num_instructions;
}

void print_instruction_table()
{
    printf("Instruction table:\n");
    for (int i = 0; i < instruction_table.size; i++)
    {
        printf("%5s %c 0x%02x 0x%02x",
               instruction_table.instructions[i].name,
               instruction_table.instructions[i].type,
               instruction_table.instructions[i].funct,
               instruction_table.instructions[i].opcode);
    }
}