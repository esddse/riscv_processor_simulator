#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "memory_system.h"

// void DEBUG(char* p1, ...);
void DEBUG_MESSAGE(char* message);
void DEBUG_INST(char* inst_name, char* type, Riscv64_decoder*, Riscv64_register*);

#endif