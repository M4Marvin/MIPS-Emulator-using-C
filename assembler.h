#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdint.h>

#define MAX_NUM_INSTRUCTIONS 256 // Maximum number of instructions
#define MAX_LINE_LENGTH 256      // Maximum length of an instruction

extern uint32_t bytecode[MAX_NUM_INSTRUCTIONS];
extern char *instruction_data[MAX_NUM_INSTRUCTIONS];

void load_instruction_data(const char *filename);
void print_instruction_data();
void init_assembler(const char *instructions_data, const char *asm_file);
uint32_t assemble_instruction(char *instruction, int line_number);
void print_bytecode();
void assemble();

char *get_label(char *instruction);
int get_label_index_by_name(char *label_name);

#endif // ASSEMBLER_H