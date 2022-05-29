/**
 * Header file for opcode table module
 * This module contains the opcode table, which is used to
 * translate opcodes into function calls.
 */
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

typedef struct Instruction Instruction;
typedef struct InstructionTable InstructionTable;

extern InstructionTable instruction_table;

void print_instruction_table();
void load_instruction_table(char *filename);

#endif // INSTRUCTION_H