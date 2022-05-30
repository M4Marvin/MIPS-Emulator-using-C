/**
 * Implementation of the emulator module.
 * This module combines the assembler and the excecute modules.
 * It is responsible for parsing the input file, generating the bytecodes and executing them.
 */

#include "emulator.h"
#include "instruction.h"
#include "register.h"
#include "execute.h"
#include "assembler.h"