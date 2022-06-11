/**
 * Implementation of the instruction module.
 * This module is responsible for storing the opcodes of instructions.
 * It is also responsible for providing the opcode of the instruction.
 */
#include "instruction.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define the struct Instruction containing data common to all instructions.
typedef struct instruction_t
{
    char *name;
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

// Global variable containing the instruction table.
InstructionTable instruction_table = {NULL, 0};

/**
 * Load the instruction table from a file.
 * @param filename The name of the file containing the instruction table.
 */
void load_instruction_table(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open instruction file.\n");
        exit(1);
    }

    // Read the number of instructions.
    int num_instructions = 0;
    fscanf(file, "%d\n", &num_instructions);

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
        int funct;
        int opcode;
        // Reading values from a line.
        fscanf(file, "%s %c %d %d\n", name, &type, &opcode, &funct);
        // Store the values in the instruction.
        instruction_table.instructions[i].name = malloc(strlen(name) + 1);
        strcpy(instruction_table.instructions[i].name, name);
        instruction_table.instructions[i].type = type;
        instruction_table.instructions[i].funct = funct;
        instruction_table.instructions[i].opcode = opcode;
    }

    // Close the file.
    fclose(file);

    // Set the size of the instruction table.
    instruction_table.size = num_instructions;
}

/**
 * Print the instruction table.
 */
void print_instruction_table()
{
    printf("Instruction table:\n");
    for (int i = 0; i < instruction_table.size; i++)
        printf("%2d. %5s %c 0x%02x 0x%02x\n",
               i + 1,
               instruction_table.instructions[i].name,
               instruction_table.instructions[i].type,
               instruction_table.instructions[i].funct,
               instruction_table.instructions[i].opcode);
}

/**
 * Add an instruction to the instruction table.
 * @param name The name of the instruction.
 * @param type The type of the instruction.
 * @param funct The funct of the instruction.
 * @param opcode The opcode of the instruction.
 */
void add_instruction(char *name, char type, uint8_t funct, uint8_t opcode)
{
    // Allocate memory for the instruction.
    Instruction *instruction = malloc(sizeof(Instruction));
    if (instruction == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for instruction.\n");
        exit(1);
    }

    // Store the values in the instruction.
    instruction->name = malloc(strlen(name) + 1);
    strcpy(instruction->name, name);
    instruction->type = type;
    instruction->funct = funct;
    instruction->opcode = opcode;

    // Add the instruction to the instruction table.
    instruction_table.instructions = realloc(instruction_table.instructions,
                                             (instruction_table.size + 1) * sizeof(Instruction));
    if (instruction_table.instructions == NULL)
    {
        fprintf(stderr, "Error: Could not allocate memory for instructions.\n");
        exit(1);
    }
    instruction_table.instructions[instruction_table.size] = *instruction;
    instruction_table.size++;
}

/**
 * Store the instruction table in a file.
 * @param filename The name of the file to store the instruction table.
 */
void store_instruction_table(char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Error: Could not open instruction file.\n");
        exit(1);
    }

    // Write the number of instructions.
    fprintf(file, "%d\n", instruction_table.size);

    // Write the instructions.
    // The format of the file is:
    // <name> <description> <type> <funct> <opcode>
    for (int i = 0; i < instruction_table.size; i++)
        fprintf(file, "%s %c %d %d\n",
                instruction_table.instructions[i].name,
                instruction_table.instructions[i].type,
                instruction_table.instructions[i].opcode,
                instruction_table.instructions[i].funct);

    // Close the file.
    fclose(file);
}

char get_instruction_type_by_name(char *name)
{
    for (int i = 0; i < instruction_table.size; i++)
        if (strcmpi(instruction_table.instructions[i].name, name) == 0)
            return instruction_table.instructions[i].type;

    return '\0';
}

uint8_t get_instruction_funct_by_name(char *name)
{
    for (int i = 0; i < instruction_table.size; i++)
        if (strcmpi(instruction_table.instructions[i].name, name) == 0)
            return instruction_table.instructions[i].funct;

    return -1;
}

uint8_t get_instruction_opcode_by_name(char *name)
{
    for (int i = 0; i < instruction_table.size; i++)
        if (strcmpi(instruction_table.instructions[i].name, name) == 0)
            return instruction_table.instructions[i].opcode;

    return -1;
}

int get_instruction_index(char *name)
{
    for (int i = 0; i < instruction_table.size; i++)
        if (strcmpi(instruction_table.instructions[i].name, name) == 0)
            return i;

    return -1;
}