#ifndef REGISTER_H
#define REGISTER_H

// Define the register table size
#define REGISTER_TABLE_SIZE 32
#define SPECIAL_REGISTER_TABLE_SIZE 3

// Register names
extern const char *REGISTER_NAMES[REGISTER_TABLE_SIZE];
extern const char *SPECIAL_REGISTER_NAMES[SPECIAL_REGISTER_TABLE_SIZE];

// Declaring the register structures
typedef struct register_entry RegisterEntry;
typedef struct register_table RegisterTable;

// Global variable to store the register table
extern RegisterTable REGISTER_TABLE;

// Register functions
void print_register(RegisterEntry *entry);
void print_register_hex(RegisterEntry *entry);

// Register table functions
void init_register_table();
int get_register_value(int index);
int get_register_value_by_name(const char *name);
int get_register_index_by_name(const char *name);
void print_register_table();
void set_register(int index, int value);

// Functions for program counter
int get_pc();
void set_pc(int value);
void increment_pc();
void jump_pc(int value);

#endif // REGISTER_H