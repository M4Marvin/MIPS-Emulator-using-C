/**
 * Implementation of the emulator module.
 * This module combines the assembler and the excecute modules.
 * It is responsible for parsing the input file, generating the bytecodes and executing them.
 */

#include "emulator.h"
#include "opcode_table.h"
#include "register.h"
#include "excecute.h"
#include "assembler.h"