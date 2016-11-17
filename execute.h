#ifndef __EXECUTE_H__
#define __EXECUTE_H__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse_elf.h"
#include "riscv_instruction.h"
#include "debug.h"

#define GET_ARRAY_LEN(array) (sizeof(array) / sizeof(array[0]))  // get the length of an array


/*********************************************/
/*                                           */
/* useful tool function here, just for debug */
/*                                           */
/*********************************************/
void print_mem(byte* start, int length); // print out a block of mem, for debug


/*********************************************/
/*                                           */
/* functions for parsing elf and load program*/
/*                                           */
/*********************************************/
void help(); // print the help information
byte* read_file(FILE* file_p, int* size);  //read the  whole file into the mem
void load_program(Elf64_Ehdr*, Riscv64_register*, Riscv64_memory*); // load program

/*********************************************/
/*                                           */
/* functions for executing instructions      */
/*                                           */
/*********************************************/
instruction fetch(Riscv64_memory*, Riscv64_register*); // fetch a instruction memory system
void decode(Riscv64_decoder*, instruction inst); // decode
void execute(Riscv64_decoder*, Riscv64_register*, Riscv64_memory*); // merge the E & M & W in one step?

#endif
