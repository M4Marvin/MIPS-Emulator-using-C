/**
 * Implementation of the assembler module.
 * This module is responsible for assembling the source code into opcodes instruction by instruction.
 */
#include "assembler.h"
#include "register.h"
#include "instruction.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

char *instruction_data[MAX_NUM_INSTRUCTIONS];
uint32_t bytecode[MAX_NUM_INSTRUCTIONS];
int instruction_count = 0;

char *label_name[MAX_NUM_INSTRUCTIONS];
int label_index[MAX_NUM_INSTRUCTIONS];
int label_count;

#define INIT_PC 0x00400000

/**
 * Loads the instructions from an assembly file.
 * @param filename Name of the file to load the data from
 */
void load_instruction_data(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int line_number = 0;
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        // Remove newline character.
        line[strcspn(line, "\n")] = 0;
        instruction_data[line_number] = (char *)malloc(strlen(line) + 1);
        strcpy(instruction_data[line_number], line);
        line_number++;
    }
    instruction_count = line_number;
    fclose(file);
}

/**
 * Print instructions loaded from the file
 */
void print_instruction_data()
{
    printf("Instruction data:\n");

    for (int i = 0; i < MAX_NUM_INSTRUCTIONS; i++)
        if (instruction_data[i] != NULL)
            printf("%s\n", instruction_data[i]);
}

/**
 * Initializes the assembler module.
 * @param instructions_data Filename of the file containing the instructions list
 * @param asm_file Filename of the file containing the assembly code
 */
void init_assembler(const char *instructions_data, const char *asm_file)
{
    for (int i = 0; i < MAX_NUM_INSTRUCTIONS; i++)
        bytecode[i] = 0;

    load_instruction_data(asm_file);

    // Load the instructions table.
    load_instruction_table(instructions_data);

    // Initialize the register table.
    init_register_table();

    // Initialize the label table.
    label_count = 0;
}
/**
 * Parses the instructions line by line and assembles them into bytecode. Also loads the label table.
 */
void assemble()
{
    // Get labels.
    for (int i = 0; i < instruction_count; i++)
        if (instruction_data[i] != NULL)
        {
            char *label = get_label(instruction_data[i]);
            if (label != NULL)
            {
                label_name[label_count] = (char *)malloc(strlen(label) + 1);
                strcpy(label_name[label_count], label);
                label_index[label_count] = i;
                label_count++;
            }
        };

    // Assemble the instructions.
    for (int i = 0; i < instruction_count; i++)
        if (instruction_data[i] != NULL)
            bytecode[i] = assemble_instruction(instruction_data[i], i);

    // Print the bytecode.
    print_bytecode();
}

/**
 * Converts a single instruction into bytecode.
 * @param instruction The instruction to convert
 * @param line_number The line number of the instruction
 */
uint32_t assemble_instruction(char *instruction, int line_number)
{
    char *token;
    char delim[] = " ,";
    uint32_t opcode = 0;
    uint32_t funct = 0;

    // Make a copy of the instruction string using stringdup.
    char *instruction_copy = strdup(instruction);

    // Split the instruction into tokens.
    token = strtok(instruction_copy, delim);

    // Check if the instruction is a comment.
    if (token[0] == '#')
        return 0;

    // Check if the instruction is a blank line.
    if (token == NULL)
        return 0;

    // Check if the instruction has a label.
    if (token[strlen(token) - 1] == ':')
    {
        token = strtok(NULL, delim);
        // Check if the remaining instruction is a blank line.
        if (token == NULL)
            return 0;
    }
    // Check if instruction is nop.
    if (strcmp(token, "nop") == 0)
    {
        return 0;
    }

    // Check if instruction list contains the instruction.
    if (get_instruction_index(token) == -1)
    {
        printf("Error: Instruction %s not found.\n", token);
        exit(1);
    }

    // Create a temporary bytecode variable.
    int32_t tempBytecode = 0;

    // Get the opcode and  adding it to the bytecode.
    opcode = get_instruction_opcode_by_name(token);
    tempBytecode = opcode << 26;

    // R - type instructions.
    if (opcode == 0x0)
    {
        // Get function code and adding it to the bytecode.
        funct = get_instruction_funct_by_name(token);
        tempBytecode |= (funct << 0);

        // Check if the instruction is jalr or jr.
        if (funct == 0x8 || funct == 0x9)
        {
            // Get the source register and destination address.
            uint32_t rs = 31;
            uint32_t address = get_register_index_by_name(strtok(NULL, delim));

            // Check if the instruction is jr.
            if (funct == 0x8)
                rs = 0;

            tempBytecode |= (address << 21) | (rs << 11);
        }

        // Check if the instruction is sll or srl.
        else if (funct == 0x0 || funct == 0x2)
        {
            // Get the source register, destination register and shift amount.
            token = strtok(NULL, delim);
            uint32_t rd = get_register_index_by_name(token);
            token = strtok(NULL, delim);
            uint32_t rt = get_register_index_by_name(token);
            token = strtok(NULL, delim);
            uint32_t shamt = atoi(token);
            // check if shamt is negative.
            if (shamt < 0)
                shamt = 0x20 + shamt;

            // Add the register values and shift amount to the bytecode.
            tempBytecode |= (rt << 16) | (rd << 11) | (shamt << 6);
        }

        // Check if the instruction is one of add, sub, div, nor, xor, or.
        else if (funct == 0x20 || funct == 0x24 || funct == 0x25 || funct == 0x26 || funct == 0x27)
        {
            // Get the register values.
            token = strtok(NULL, delim);
            uint32_t rd = get_register_index_by_name(token);
            token = strtok(NULL, delim);
            uint32_t rs = get_register_index_by_name(token);
            token = strtok(NULL, delim);
            uint32_t rt = get_register_index_by_name(token);

            // Add the register values to the bytecode.
            tempBytecode |= (rs << 21) | (rt << 16) | (rd << 11);
        }
    }

    // I-type instruction
    else if ((opcode >= 0x4 && opcode <= 0x8) || opcode == 0xA || opcode == 0xC || opcode == 0xE)
    {
        uint32_t rs, rt;
        uint16_t imm;
        token = strtok(NULL, delim);
        rs = get_register_index_by_name(token);
        token = strtok(NULL, delim);

        // Check if the instruction is beq or bne.
        if (opcode == 0x4 || opcode == 0x5)
        {
            // Get the register value and adding it to the bytecode.
            rt = get_register_index_by_name(token);
            tempBytecode |= (rs << 21) | (rt << 16);

            // Calculate the offset of branching.
            token = strtok(NULL, delim);
            uint32_t jump_to = get_label_index_by_name(token);
            uint32_t jump_from = line_number;
            uint16_t offset = jump_to - jump_from - 1;

            // Check if offset is negative, if so then take 2's complement.
            if (offset < 0)
                offset = ~offset + 1;

            // Add the offset to the bytecode.
            tempBytecode |= offset;
        }

        // Check if the instruction is blez or bgtz.
        else if (opcode == 0x6 || opcode == 0x7)
        {
            // Calculating the offset and adding it to the bytecode.
            uint32_t jump_to = get_label_index_by_name(token);
            uint32_t jump_from = line_number;
            uint16_t offset = jump_to - jump_from - 1;

            // Check if offset is negative, if so then take 2's complement.
            if (offset < 0)
                offset = ~offset + 1;

            tempBytecode |= (rs << 21) | (offset << 0);
        }

        // Remaining I-type instructions. (addi, andi, subi, ori)
        else
        {
            rt = get_register_index_by_name(token);
            token = strtok(NULL, delim);
            imm = atoi(token);

            // Check if imm is negative. If so, get the two's complement.
            if (imm < 0)
                imm = ~imm + 1;

            tempBytecode |= (rs << 16) | (rt << 21) | (imm << 0);
        }
    }

    // J-type instruction
    else if (opcode == 0x2 || opcode == 0x3)
    {
        token = strtok(NULL, delim);
        uint32_t address = get_label_index_by_name(token);

        // calculate the address to jump to.
        address = INIT_PC + address * 4;

        // Add the address to the bytecode.
        tempBytecode |= ((address >> 2) & 0x3FFFFF);
    }
    return tempBytecode;
}

/*
 * Extracts the label from the instruction.
 */
char *get_label(char *instruction)
{
    char *token;
    char delim[] = " ";
    char *instruction_copy = strdup(instruction);
    token = strtok(instruction_copy, delim);
    if (token == NULL)
        return NULL;
    if (token[strlen(token) - 1] == ':')
    {
        // Remove the colon from the label.
        token[strlen(token) - 1] = '\0';
        return token;
    }
    return NULL;
}

/**
 * Returns the index of the label in the label table.
 */
int get_label_index_by_name(char *label)
{
    for (int i = 0; i < label_count; i++)
    {
        if (strcmp(label, label_name[i]) == 0)
        {
            return label_index[i];
        }
    }
    return -1;
}

/**
 * Print the bytecode.
 */

void print_bytecode()
{
    for (int i = 0; i < instruction_count; i++)
    {
        printf("0x%08x   0x%08x  %s\n", INIT_PC + i * 4, bytecode[i], instruction_data[i]);
    }
}