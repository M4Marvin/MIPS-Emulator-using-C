/**
 * Implementation of the register module.
 * This module is responsible for storing the symbols and their values.
 */
#include "register.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variable to store the register names
const char *REGISTER_NAMES[] = {"$zero",
                                "$at", "$v0", "$v1",
                                "$a0", "$a1", "$a2", "$a3",
                                "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7",
                                "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7",
                                "$t8", "$t9",
                                "$k0", "$k1",
                                "$gp",
                                "$sp", "$fp", "$ra"};

// Global variable to store the special register names
const char *SPECIAL_REGISTER_NAMES[] = {"$pc", "$hi", "$lo"};

#define INIT_PC 0x00400000

// Structure definition for the register entry
typedef struct register_entry
{
    const char *name;
    int value;
} RegisterEntry;

typedef struct register_table
{
    RegisterEntry *registers[REGISTER_TABLE_SIZE];                // For storing the standard 32 registers
    RegisterEntry *specialRegisters[SPECIAL_REGISTER_TABLE_SIZE]; // For pc, hi, lo
} RegisterTable;

RegisterTable REGISTER_TABLE;

/**
 * Print the register entry.
 * @param entry The register entry to be printed.
 */
void print_register(RegisterEntry *entry)
{
    printf("%5s: %d\n", entry->name, entry->value);
}

/**
 * Print the register entry in hexadecimal values.
 * @param entry The register entry to be printed.
 */
void print_register_hex(RegisterEntry *entry)
{
    printf("%s: 0x%08x\n", entry->name, entry->value);
}

/**
 * Initialize the register table.
 * This function is responsible for initializing all the register values to 0, except for the pc (set to 0x00400000).
 */
void init_register_table()
{
    for (int i = 0; i < REGISTER_TABLE_SIZE; i++)
    {
        REGISTER_TABLE.registers[i] = malloc(sizeof(RegisterEntry));
        REGISTER_TABLE.registers[i]->name = REGISTER_NAMES[i];
        REGISTER_TABLE.registers[i]->value = 0;
    }

    for (int i = 0; i < SPECIAL_REGISTER_TABLE_SIZE; i++)
    {
        REGISTER_TABLE.specialRegisters[i] = malloc(sizeof(RegisterEntry));
        REGISTER_TABLE.specialRegisters[i]->name = SPECIAL_REGISTER_NAMES[i];
        REGISTER_TABLE.specialRegisters[i]->value = 0;
    }

    // Set the pc to the start of the program
    REGISTER_TABLE.specialRegisters[0]->value = INIT_PC;
}

/**
 * Print the register table.
 */
void print_register_table()
{
    printf("\n\nRegister Table:\n");
    for (int i = 0; i < REGISTER_TABLE_SIZE; i++)
    {
        printf("%2d: ", i);
        print_register_hex(REGISTER_TABLE.registers[i]);
    }

    for (int i = 0; i < SPECIAL_REGISTER_TABLE_SIZE; i++)
    {
        print_register_hex(REGISTER_TABLE.specialRegisters[i]);
    }
}

/**
 * Get the register entry by index.
 * @param index The index of the register entry.
 * @return The register value.
 */
int get_register_value(int index)
{
    if (index < 0 || index >= REGISTER_TABLE_SIZE)
    {
        printf("Invalid register index: %d\n", index);
        return -1;
    }
    else
    {
        return REGISTER_TABLE.registers[index]->value;
    }
}

/**
 * Get the register entry by name.
 * @param name The name of the register entry.
 * @return The register value.
 */
int get_register_value_by_name(const char *name)
{
    for (int i = 0; i < REGISTER_TABLE_SIZE; i++)
    {
        if (strcmp(REGISTER_TABLE.registers[i]->name, name) == 0)
        {
            return REGISTER_TABLE.registers[i]->value;
        }
    }

    for (int i = 0; i < SPECIAL_REGISTER_TABLE_SIZE; i++)
    {
        if (strcmp(REGISTER_TABLE.specialRegisters[i]->name, name) == 0)
        {
            return REGISTER_TABLE.specialRegisters[i]->value;
        }
    }

    printf("Invalid register name: %s\n", name);
    return -1;
}

/**
 * Set the register entry by index. Stores negative values as twos complement.
 * @param index The index of the register entry.
 * @param value The value to be set.
 */
void set_register_by_index(int index, int value)
{
    if (index < 0 || index >= REGISTER_TABLE_SIZE)
    {
        printf("Invalid register index: %d\n", index);
    }
    else
    {
        // Check if the value is negative
        if (value < 0)
        {
            // Convert the value to twos complement (32-bit)
            value = ~value;
            value = value + 1;
        }
        // Store the value
        REGISTER_TABLE.registers[index]->value = value;
    }
}

/**
 * Set the register entry by name. Stores negative values as twos complement.
 * @param name The name of the register entry.
 * @param value The value to be set.
 */
void set_register_by_name(const char *name, int value)
{
    for (int i = 0; i < REGISTER_TABLE_SIZE; i++)
    {
        if (strcmp(REGISTER_TABLE.registers[i]->name, name) == 0)
        {
            // Check if the value is negative
            if (value < 0)
            {
                // Convert the value to twos complement (32-bit)
                value = ~value;
                value = value + 1;
            }
            // Store the value
            REGISTER_TABLE.registers[i]->value = value;
            return;
        }
    }

    for (int i = 0; i < SPECIAL_REGISTER_TABLE_SIZE; i++)
    {
        if (strcmp(REGISTER_TABLE.specialRegisters[i]->name, name) == 0)
        {
            // Check if the value is negative
            if (value < 0)
            {
                // Convert the value to twos complement (32-bit)
                value = ~value;
                value = value + 1;
            }
            // Store the value
            REGISTER_TABLE.specialRegisters[i]->value = value;
            return;
        }
    }

    printf("Invalid register name: %s\n", name);
}

/**
 * Get the value of the program counter.
 * @return The value of the program counter.
 */
int get_pc()
{
    return REGISTER_TABLE.specialRegisters[0]->value;
}

/**
 * Set the value of the program counter.
 * @param value The value of the program counter.
 */
void set_pc(int value)
{
    REGISTER_TABLE.specialRegisters[0]->value = INIT_PC + value * 4;
}

/**
 * Increment the value of the program counter.
 */
void increment_pc()
{
    REGISTER_TABLE.specialRegisters[0]->value += 4;
}

/**
 * Jumping forward or backward in the program by a certain number of instructions.
 */
void jump_pc(int value)
{
    REGISTER_TABLE.specialRegisters[0]->value += value * 4;
    if (REGISTER_TABLE.specialRegisters[0]->value < INIT_PC)
    {
        printf("Invalid jump: %d\n", value);
        REGISTER_TABLE.specialRegisters[0]->value = INIT_PC;
    }
}
