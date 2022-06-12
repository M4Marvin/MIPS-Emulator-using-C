/**
 * Header file for opcode table module
 * This module contains the opcode table, which is used to
 * translate opcodes into function calls.
 */
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <stdint.h>

typedef struct instruction_t Instruction;
typedef struct InstructionTable InstructionTable;

extern InstructionTable instruction_table;

void print_instruction_table();
void load_instruction_table(const char *filename);
void add_instruction(char *name, char type, uint8_t funct, uint8_t opcode);
void store_instruction_table(char *filename);
char get_instruction_type_by_name(char *name);
uint8_t get_instruction_funct_by_name(char *name);
uint8_t get_instruction_opcode_by_name(char *name);
int get_instruction_index(char *name);

#endif // INSTRUCTION_H